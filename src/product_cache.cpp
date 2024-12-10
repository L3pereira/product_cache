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

    // Cache miss: fetch from the database, but first release the cache lock to prevent blocking
    lock.unlock(); // Unlock the cache to allow other threads to access the cache

    // If not in cache, fetch from the database
    auto db_product = _db->fetchProductDetails(product_id);

    // Re-lock the cache to update it
    lock.lock(); // Re-acquire the cache lock for writing to the cache

    // Double-check the cache in case another thread has inserted the product in the meantime
    cached_product = _cache->get(product_id);
    if (cached_product.has_value())
    {
        return cached_product;
    }

    if (db_product.has_value())
    {
        _cache->put(product_id, db_product.value()); // Cache the fetched product
    }
    return db_product;
}

// Fetch products by category
std::vector<Product> ProductCache::fetchProductsByCategory(uint32_t category_id)
{
    // No cache mechanism for categories; query the database directly
    return _db->fetchProductsByCategory(category_id);
}
