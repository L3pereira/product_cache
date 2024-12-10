#ifndef MOCKPRODUCTDATABASE_H
#define MOCKPRODUCTDATABASE_H

#include "product.h"
#include <unordered_map>
#include <vector>
#include <optional>

// Mock database class for testing
class MockProductDatabase : public IDatabase
{
public:
    // Override fetchProductDetails for testing purposes
    std::optional<Product> fetchProductDetails(uint64_t product_id) override
    {
        // Simulated product data for testing
        auto it = _mock_data.find(product_id);
        return (it != _mock_data.end()) ? std::make_optional(it->second) : std::nullopt;
    }

    // Override fetchProductsByCategory for testing purposes
    std::vector<Product> fetchProductsByCategory(uint32_t category_id) override
    {
        // Simulated category data for testing
        auto it = _mock_categories.find(category_id);
        return (it != _mock_categories.end()) ? it->second : std::vector<Product>{};
    }

private:
    // Mock product data
    static const inline std::unordered_map<uint64_t, Product> _mock_data = {
        {1, {1, 101, "Laptop", "High-end gaming laptop", {}}},
        {2, {2, 101, "Gaming Mouse", "Precision gaming mouse", {}}},
        {3, {3, 102, "Phone", "Latest smartphone", {}}},
        {4, {4, 103, "Tablet", "Compact and powerful tablet", {}}}};

    // Mock category data
    static const inline std::unordered_map<uint32_t, std::vector<Product>> _mock_categories = {
        {101, {{1, 101, "Laptop", "High-end gaming laptop", {}}, {2, 101, "Gaming Mouse", "Precision gaming mouse", {}}}},
        {102, {{3, 102, "Phone", "Latest smartphone", {}}}},
        {103, {{4, 103, "Tablet", "Compact and powerful tablet", {}}}}};
};

#endif // MOCKPRODUCTDATABASE_H