#include "product_cache.h"

// Static default database instance
static ProductDatabase default_db; // Default ProductDatabase object

// Constructor for ProductCache
ProductCache::ProductCache(size_t cache_capacity, std::unique_ptr<ProductDatabase> db)
    : _db(db ? std::move(db) : std::make_unique<ProductDatabase>(default_db)),
      _cache(std::make_unique<LRUCache<uint64_t, Product>>(cache_capacity)) {} // Use default_db if db is nullptr

// Fetch product details from cache or database
std::optional<Product> ProductCache::getProduct(uint64_t product_id)
{
    // Try to fetch from cache (shared access)
    {
        std::shared_lock<std::shared_mutex> lock(_cache_mutex);
        auto cached_product = _cache->get(product_id);
        if (cached_product.has_value())
        {
            return cached_product; // Return cached product if found
        }
    }

    // If not in cache, fetch from the database (exclusive write access)
    std::unique_lock<std::shared_mutex> lock(_cache_mutex);
    auto db_product = _db->fetchProductDetails(product_id);
    if (db_product.has_value())
    {
        _cache->put(product_id, db_product.value()); // Cache the fetched product
    }
    return db_product;
}
