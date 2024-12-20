#ifndef IDATABASE_H
#define IDATABASE_H

#include <optional>
#include "product.h"

class IDatabase
{
public:
    virtual ~IDatabase() = default;

    // Fetch product details by ID
    virtual std::optional<Product> fetchProductDetails(uint64_t product_id) = 0;

    // Fetch products by category
    virtual std::vector<Product> fetchProductsByCategory(uint32_t category_id) = 0;
};

#endif // IDATABASE_H
