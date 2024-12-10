#include "product_cache.h"
#include "product_database.h"
#include "lru_cache.h"
#include <memory>
#include <shared_mutex>

#include <mutex>

// Constructor for ProductCache
ProductCache::ProductCache(std::shared_ptr<IDatabase> db,
                           std::shared_ptr<ICache<uint64_t, Product>> cache)
    : _db(std::move(db)),
      _cache(std::move(cache)) {}

// Fetch product details from cache or database
std::optional<Product> ProductCache::fetchProductDetails(uint64_t product_id)
{
    std::unique_lock<std::shared_mutex> lock(_cache_mutex); // Exclusive lock for both read and write
    auto cached_product = _cache->get(product_id);
    if (cached_product.has_value())
    {
        return cached_product; // Return cached product if found
    }

    // If not in cache, fetch from the database
    auto db_product = _db->fetchProductDetails(product_id);
    if (db_product.has_value())
    {
        _cache->put(product_id, db_product.value()); // Cache the fetched product
    }
    return db_product;
}
