#ifndef PRODUCTCACHE_H
#define PRODUCTCACHE_H

#include "LRUCache.h"
#include "Product.h"

// Class to manage product queries and cache
class ProductCache {
private:
    ProductDatabase db;                    // Instance of the database
    LRUCache<uint64_t, Product> cache;     // LRU cache for product details

public:
    // Constructor to initialize the cache with a given capacity
    explicit ProductCache(size_t cache_capacity) : cache(cache_capacity) {}

    // Fetch product details from cache or database
    std::optional<Product> getProduct(uint64_t product_id) {
        // Try to fetch from cache
        auto cached_product = cache.get(product_id);
        if (cached_product.has_value()) {
            return cached_product; // Return cached product if found
        }

        // If not in cache, fetch from the database
        auto db_product = db.fetchProductDetails(product_id);
        if (db_product.has_value()) {
            cache.put(product_id, db_product.value()); // Cache the fetched product
        }
        return db_product;
    }
};

#endif // PRODUCTCACHE_H
