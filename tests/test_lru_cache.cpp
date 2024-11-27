#include "lru_cache.h"
#include <gtest/gtest.h>

// Test for basic insertion and retrieval
TEST(lru_cache_test, basic_insertion_retrieval) {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");

    // Check values are correctly inserted
    EXPECT_EQ(cache.get(1).value_or(""), "one");
    EXPECT_EQ(cache.get(2).value_or(""), "two");
}

// Test for eviction policy
TEST(lru_cache_test, eviction_policy) {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three"); // Evicts key 1

    // Key 1 should be evicted
    EXPECT_EQ(cache.get(1).value_or("Not Found"), "Not Found");

    // Keys 2 and 3 should be present
    EXPECT_EQ(cache.get(2).value_or(""), "two");
    EXPECT_EQ(cache.get(3).value_or(""), "three");
}

// Test for accessing non-existent keys
TEST(lru_cache_test, missing_key) {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");

    // Key 2 was never added
    EXPECT_EQ(cache.get(2).value_or("Not Found"), "Not Found");
}
