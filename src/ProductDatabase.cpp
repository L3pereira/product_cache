#include "ProductDatabase.h"
#include <unordered_map>

// Simulated database with hardcoded products
std::optional<Product> ProductDatabase::fetchProductDetails(uint64_t product_id) const {
    static const std::unordered_map<uint64_t, Product> database = {
        {1, {1, 101, "Laptop", "High-end gaming laptop", {0xAA, 0xBB}}},
        {2, {2, 102, "Phone", "Latest smartphone", {0xCC, 0xDD}}}
    };

    auto it = database.find(product_id);
    return (it != database.end()) ? std::make_optional(it->second) : std::nullopt;
}
