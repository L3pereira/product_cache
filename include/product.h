#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

// Structure to represent product details
struct Product {
    uint64_t id;                // Product ID
    uint32_t category;          // Product category
    std::string name;           // Product name
    std::string description;    // Product description
    std::vector<uint8_t> thumbnail; // Thumbnail image data
};

#endif // PRODUCT_H
