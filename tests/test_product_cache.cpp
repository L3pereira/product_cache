#include "product_cache.h"
#include "mock_product_database.h"
#include <gtest/gtest.h>

// Test for basic product retrieval
TEST(product_cache_test, basic_retrieval) {
    // Create a ProductCache instance with the mock database
    MockProductDatabase mock_db;
    ProductCache cache(2, &mock_db); // Pass mock database to ProductCache

    // Fetch a product (should come from the mock database)
    auto product = cache.getProduct(1);
    ASSERT_TRUE(product.has_value());
    EXPECT_EQ(product->name, "Laptop");

    // Fetch the same product again (should come from cache)
    auto cached_product = cache.getProduct(1);
    ASSERT_TRUE(cached_product.has_value());
    EXPECT_EQ(cached_product->name, "Laptop");
}

// Test for cache eviction
TEST(product_cache_test, eviction_policy) {
    // Create a ProductCache instance with the mock database
    MockProductDatabase mock_db;
    ProductCache cache(2, &mock_db); // Pass mock database to ProductCache

    // Add two products to the cache
    cache.getProduct(1);
    cache.getProduct(2);

    // Add a third product (evicts the least recently used, which is product 1)
    cache.getProduct(3);

    // Product 1 should no longer be in the cache
    auto evicted_product = cache.getProduct(1); // Fetches from database again
    ASSERT_TRUE(evicted_product.has_value());
    EXPECT_EQ(evicted_product->name, "Laptop");
}

// Test for missing product
TEST(product_cache_test, missing_product) {
    // Create a ProductCache instance with the mock database
    MockProductDatabase mock_db;
    ProductCache cache(2, &mock_db); // Pass mock database to ProductCache

    // Fetch a non-existent product ID
    auto missing_product = cache.getProduct(999);
    EXPECT_FALSE(missing_product.has_value());
}
