#include "ProductCache.h"
#include <iostream>
#include <thread>

// Simulate a client fetching and printing product details
void fetchAndPrint(ProductCache& cache, uint64_t product_id) {
    auto product = cache.getProduct(product_id);
    if (product.has_value()) {
        std::cout << "Fetched Product: " << product->name 
                  << " [ID: " << product->id << "]\n";
    } else {
        std::cout << "Product not found [ID: " << product_id << "]\n";
    }
}

int main() {
    // Initialize the cache with a capacity of 2 items
    ProductCache cache(2);

    // Simulate concurrent product queries
    std::thread t1(fetchAndPrint, std::ref(cache), 1); // Fetch product 1
    std::thread t2(fetchAndPrint, std::ref(cache), 2); // Fetch product 2
    std::thread t3(fetchAndPrint, std::ref(cache), 1); // Fetch product 1 again

    // Join threads
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
