#ifndef PRODUCTCACHE_H
#define PRODUCTCACHE_H

#include "product.h"
#include "lru_cache.h"
#include "product_database.h"
#include <optional>
#include <mutex>

// Class to manage product queries and cache
class ProductCache {
public:
    // Constructor declaration
    explicit ProductCache(size_t cache_capacity, ProductDatabase* db = nullptr);

    // Fetch product details by ID (users can access the product's fields)
    std::optional<Product> getProduct(uint64_t product_id);

private:
    ProductDatabase* db;            // Instance of ProductDatabase (hidden)
    LRUCache<uint64_t, Product> cache;  // LRU cache for product details
    std::mutex mutex_;  // Mutex to ensure thread-safe access
};

#endif // PRODUCTCACHE_H
