#ifndef PRODUCTDATABASE_H
#define PRODUCTDATABASE_H

#include "product.h"
#include <optional>

// ProductDatabase class to simulate product storage and access
class ProductDatabase
{
public:
    // Fetch product details by ID (returns nullopt if not found)
    virtual std::optional<Product> fetchProductDetails(uint64_t product_id) const;
};

#endif // PRODUCTDATABASE_H
