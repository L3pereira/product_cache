#ifndef PRODUCTCACHE_H
#define PRODUCTCACHE_H

#include "product.h"
#include "lru_cache.h"
#include "product_database.h"
#include <optional>
#include <memory> // For std::unique_ptr
#include <shared_mutex>
#include <mutex>

// Class to manage product queries and cache
class ProductCache
{
public:
    // Constructor declaration
    explicit ProductCache(size_t cache_capacity, std::unique_ptr<ProductDatabase> db = nullptr);

    // Fetch product details by ID (users can access the product's fields)
    std::optional<Product> getProduct(uint64_t product_id);

private:
    std::unique_ptr<ProductDatabase> _db;                // Exclusive ownership of ProductDatabase
    std::unique_ptr<LRUCache<uint64_t, Product>> _cache; // Exclusive ownership of LRUCache
    std::shared_mutex _cache_mutex;                      // Mutex to ensure thread-safe access to cache
};

#endif // PRODUCTCACHE_H
