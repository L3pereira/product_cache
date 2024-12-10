#include "product_cache.h"
#include "mock_product_database.h"
#include <gtest/gtest.h>

// Test for basic category retrieval
TEST(product_category_tests, basic_category_retrieval)
{
    // Create a mock database
    auto mock_db = std::make_shared<MockProductDatabase>();

    // Create ProductCache with mocked database
    ProductCache cache_manager(mock_db, nullptr); // No cache for this test

    // Fetch products for category 101 (should come from the mock database)
    auto products = cache_manager.fetchProductsByCategory(101);
    ASSERT_EQ(products.size(), 2); // Verify size
    EXPECT_EQ(products[0].name, "Laptop");
    EXPECT_EQ(products[1].name, "Gaming Mouse");

    // Fetch products for category 102
    auto products2 = cache_manager.fetchProductsByCategory(102);
    ASSERT_EQ(products2.size(), 1); // Only one product in category 102
    EXPECT_EQ(products2[0].name, "Phone");
}

// Test for missing category (no products in category)
TEST(product_category_tests, missing_category)
{
    // Create a mock database
    auto mock_db = std::make_shared<MockProductDatabase>();

    // Create ProductCache with mocked database
    ProductCache cache_manager(mock_db, nullptr); // No cache for this test

    // Fetch a non-existent category ID (should return an empty vector)
    auto products = cache_manager.fetchProductsByCategory(999);
    ASSERT_TRUE(products.empty()); // No products in this category
}
