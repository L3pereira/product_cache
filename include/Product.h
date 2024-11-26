#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

// Structure to represent product details
struct Product {
    uint64_t id;                // Product ID
    uint32_t category;          // Product category
    std::string name;           // Product name
    std::string description;    // Product description
    std::vector<uint8_t> thumbnail; // Thumbnail image data
};

// Mock database class simulating product storage
class ProductDatabase {
public:
    // Fetch product details by ID (returns nullopt if not found)
    virtual std::optional<Product> fetchProductDetails(uint64_t product_id) const {
        // Simulated database with hardcoded products
        static const std::unordered_map<uint64_t, Product> database = {
            {1, {1, 101, "Laptop", "High-end gaming laptop", {0xAA, 0xBB}}},
            {2, {2, 102, "Phone", "Latest smartphone", {0xCC, 0xDD}}}
        };

        auto it = database.find(product_id);
        return (it != database.end()) ? std::make_optional(it->second) : std::nullopt;
    }
};

#endif // PRODUCT_H
