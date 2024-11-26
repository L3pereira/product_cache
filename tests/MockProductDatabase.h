#ifndef MOCKPRODUCTDATABASE_H
#define MOCKPRODUCTDATABASE_H

#include "Product.h"
#include <unordered_map>
#include <optional>

// Mock database class for testing
class MockProductDatabase : public ProductDatabase {
public:
    // Override fetchProductDetails for testing purposes
    std::optional<Product> fetchProductDetails(uint64_t product_id) const override {
        // Simulated data for testing
        static const std::unordered_map<uint64_t, Product> mock_data = {
            {1, {1, 101, "Laptop", "High-end gaming laptop", {}}},
            {2, {2, 102, "Phone", "Latest smartphone", {}}},
            {3, {3, 103, "Tablet", "Compact and powerful tablet", {}}}
        };

        // Return product if found, otherwise std::nullopt
        auto it = mock_data.find(product_id);
        return (it != mock_data.end()) ? std::make_optional(it->second) : std::nullopt;
    }
};

#endif // MOCKPRODUCTDATABASE_H
