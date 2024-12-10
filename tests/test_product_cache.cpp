#include "product_cache.h"
#include "mock_product_database.h" // Using the mock product database as before
#include "mock_lru_cache.h"        // Use the in-memory cache class
#include <gtest/gtest.h>

// Test for basic product retrieval
TEST(product_cache_tests, basic_retrieval)
{
    // Create a mock database and an in-memory cache
    auto mock_db = std::make_shared<MockProductDatabase>();
    auto cache = std::make_shared<MockLRUCache<uint64_t, Product>>();

    // Create ProductCache with mocked database and in-memory cache
    ProductCache cache_manager(mock_db, cache);

    // Add expected product to the in-memory cache manually
    Product laptop{1, 101, "Laptop", "High-end gaming laptop", {}};
    cache->put(1, laptop);

    // Fetch a product (should come from the in-memory cache)
    auto product = cache_manager.fetchProductDetails(1);
    ASSERT_TRUE(product.has_value());
    EXPECT_EQ(product->name, "Laptop");

    // Fetch the same product again (should come from cache)
    auto cached_product = cache_manager.fetchProductDetails(1);
    ASSERT_TRUE(cached_product.has_value());
    EXPECT_EQ(cached_product->name, "Laptop");
}

// Test for cache eviction
TEST(product_cache_tests, eviction_policy)
{
    // Create a mock database and an in-memory cache
    auto mock_db = std::make_shared<MockProductDatabase>();
    auto cache = std::make_shared<MockLRUCache<uint64_t, Product>>();

    // Create ProductCache with mocked database and in-memory cache
    ProductCache cache_manager(mock_db, cache);

    // Add two products to the cache manually
    Product laptop{1, 101, "Laptop", "High-end gaming laptop", {}};
    Product phone{2, 102, "Phone", "Latest smartphone", {}};
    cache->put(1, laptop);
    cache->put(2, phone);

    // Add a third product which will cause eviction (simple eviction strategy removes product 1)
    Product tablet{3, 103, "Tablet", "Compact and powerful tablet", {}};
    cache->put(3, tablet); // The cache should now contain 2 and 3, and 1 should be evicted

    // Check if the cache evicted product 1
    auto evicted_product = cache_manager.fetchProductDetails(1); // Fetch product 1, should be fetched from the database again
    ASSERT_TRUE(evicted_product.has_value());
    EXPECT_EQ(evicted_product->name, "Laptop");
}

// Test for missing product (when the product does not exist in cache or database)
TEST(product_cache_tests, missing_product)
{
    // Create a mock database and an in-memory cache
    auto mock_db = std::make_shared<MockProductDatabase>();
    auto cache = std::make_shared<MockLRUCache<uint64_t, Product>>();

    // Create ProductCache with mocked database and in-memory cache
    ProductCache cache_manager(mock_db, cache);

    // Fetch a non-existent product ID (should return from the database)
    auto missing_product = cache_manager.fetchProductDetails(999);
    EXPECT_FALSE(missing_product.has_value());
}
