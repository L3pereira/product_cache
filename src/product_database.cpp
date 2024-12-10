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
std::optional<Product> ProductDatabase::fetchProductDetails(uint64_t product_id)
{
    auto it = _database.find(product_id);
    if (it != _database.end())
    {
        return it->second; // Return the product if found
    }
    return std::nullopt; // Return nullopt if not found
}

// Fetch products by category
std::vector<Product> ProductDatabase::fetchProductsByCategory(uint32_t category_id)
{
    std::vector<Product> products_in_category;

    // Iterate through the database to find matching products
    for (const auto &[id, product] : _database)
    {
        if (product.category == category_id)
        {
            products_in_category.push_back(product);
        }
    }

    return products_in_category;
}