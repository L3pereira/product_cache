#ifndef PRODUCTDATABASE_H
#define PRODUCTDATABASE_H

#include "idatabase.h"
#include "product.h"
#include <unordered_map>
#include <optional>

class ProductDatabase : public IDatabase
{
public:
    // Constructor to initialize the product database
    ProductDatabase();

    // Fetch product details by ID (override from IDatabase)
    std::optional<Product> fetchProductDetails(uint64_t product_id) override;

private:
    std::unordered_map<uint64_t, Product> _database; // Internal storage for products
};

#endif // PRODUCTDATABASE_H
