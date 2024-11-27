#include "ProductCache.h"
#include <mutex>

// Static default database instance
static ProductDatabase default_db;  // Default ProductDatabase object

// Constructor for ProductCache
ProductCache::ProductCache(size_t cache_capacity, ProductDatabase* db)
    : db(db ? db : &default_db), cache(cache_capacity) {}  // Use default_db if db is nullptr

// Fetch product details from cache or database
std::optional<Product> ProductCache::getProduct(uint64_t product_id) {
    std::lock_guard<std::mutex> lock(mutex_); // Ensure thread-safe access to cache
    // Try to fetch from cache
    auto cached_product = cache.get(product_id);
    if (cached_product.has_value()) {
        return cached_product; // Return cached product if found
    }

    // If not in cache, fetch from the database
    auto db_product = db->fetchProductDetails(product_id);
    if (db_product.has_value()) {
        cache.put(product_id, db_product.value()); // Cache the fetched product
    }
    return db_product;
}
