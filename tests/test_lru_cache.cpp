#include "lru_cache.h"
#include <gtest/gtest.h>

// Test for basic insertion and retrieval
TEST(lru_cache_tests, basic_insertion_retrieval)
{
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");

    // Check values are correctly inserted
    EXPECT_EQ(cache.get(1).value_or(""), "one");
    EXPECT_EQ(cache.get(2).value_or(""), "two");
}

// Test for eviction policy
TEST(lru_cache_tests, eviction_policy)
{
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three"); // Evicts key 1 (LRU)

    // Key 1 should be evicted
    EXPECT_EQ(cache.get(1).value_or("Not Found"), "Not Found");

    // Keys 2 and 3 should be present (most recently used is 3)
    EXPECT_EQ(cache.get(2).value_or(""), "two");
    EXPECT_EQ(cache.get(3).value_or(""), "three");
}

// Test for accessing non-existent keys
TEST(lru_cache_tests, missing_key)
{
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");

    // Key 2 was never added
    EXPECT_EQ(cache.get(2).value_or("Not Found"), "Not Found");
}

// Test for updating existing key
TEST(lru_cache_tests, update_existing_key)
{
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");

    // Update value for key 1
    cache.put(1, "updated_one");

    // Check if the value is updated correctly
    EXPECT_EQ(cache.get(1).value_or(""), "updated_one");
    EXPECT_EQ(cache.get(2).value_or(""), "two");
}

// Test for LRU order after access
TEST(lru_cache_tests, lru_order_after_access)
{
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.get(1);          // Access key 1 to make it most recently used
    cache.put(3, "three"); // Evicts key 2

    // Key 1 should be present (most recently used)
    EXPECT_EQ(cache.get(1).value_or(""), "one");

    // Key 2 should be evicted
    EXPECT_EQ(cache.get(2).value_or("Not Found"), "Not Found");

    // Key 3 should be present
    EXPECT_EQ(cache.get(3).value_or(""), "three");
}
