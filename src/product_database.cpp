#include "product_database.h"
#include <unordered_map>

// Constructor definition
ProductDatabase::ProductDatabase()
{
    // Initialize the database with hardcoded products
    _database = {
        {1, {1, 101, "Laptop", "High-end gaming laptop", {0xAA, 0xBB}}},
        {2, {2, 102, "Phone", "Latest smartphone", {0xCC, 0xDD}}}};
}

// Fetch product details by ID
std::optional<Product> ProductDatabase::fetchProductDetails(uint64_t product_id) const
{
    auto it = _database.find(product_id);
    if (it != _database.end())
    {
        return it->second; // Return the product if found
    }
    return std::nullopt; // Return nullopt if not found
}
