#include "product_cache.h"
#include "product_database.h"
#include "lru_cache.h"
#include <iostream>
#include <thread>
#include <memory> // For std::make_shared

// Simulate a client fetching and printing product details
void fetchAndPrint(std::shared_ptr<ProductCache> cache, uint64_t product_id)
{
    auto product = cache->fetchProductDetails(product_id);
    if (product.has_value())
    {
        std::cout << "Fetched Product: " << product->name
                  << " [ID: " << product->id << "]\n";
    }
    else
    {
        std::cout << "Product not found [ID: " << product_id << "]\n";
    }
}

int main()
{

    // Create the database and lru cache for the ProductCache
    auto db = std::make_shared<ProductDatabase>();

    // Initialize the cache with a capacity of 2 items
    auto cache = std::make_shared<LRUCache<uint64_t, Product>>(2);

    // Initialize the ProductCache with a capacity of 2 items, and pass the mock database and cache
    auto product_cache = std::make_shared<ProductCache>(db, cache);

    // Simulate concurrent product queries
    std::thread t1(fetchAndPrint, product_cache, 1); // Fetch product 1
    std::thread t2(fetchAndPrint, product_cache, 2); // Fetch product 2
    std::thread t3(fetchAndPrint, product_cache, 1); // Fetch product 1 again

    // Join threads
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
