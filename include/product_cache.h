#ifndef PRODUCTCACHE_H
#define PRODUCTCACHE_H

#include "idatabase.h"
#include "product.h"
#include "icache.h"
#include <memory>
#include <shared_mutex>

// Class to manage product queries and cache
class ProductCache : public IDatabase
{
public:
    // Declare the constructor (no definition here)
    ProductCache(std::shared_ptr<IDatabase> db,
                 std::shared_ptr<ICache<uint64_t, Product>> cache);

    // Override the fetchProductDetails method from IDatabase/Fetch product details by ID (users can access the product's fields)
    std::optional<Product> fetchProductDetails(uint64_t product_id) override;

private:
    std::shared_ptr<IDatabase> _db;                    // Exclusive ownership of ProductDatabase
    std::shared_ptr<ICache<uint64_t, Product>> _cache; // Exclusive ownership of LRUCache
    std::shared_mutex _cache_mutex;                    // Mutex to ensure thread-safe access to cache
};

#endif // PRODUCTCACHE_H
