# **Product Cache System with LRU Cache**

## **Overview**
This program simulates an e-commerce backend system where product details are fetched from a database or an in-memory cache. It is designed to optimize product lookups using an **LRU (Least Recently Used) cache** for frequently accessed items. The cache reduces expensive database calls by storing recently and frequently accessed product details.

---

## **Features**
1. **LRU Cache**:
   - Implements a thread-safe, generic in-memory cache with a fixed capacity.
   - Automatically evicts the least recently used item when full.

2. **Product Cache**:
   - Wraps the LRU cache and routes product queries.
   - Fetches product details from the database if not found in the cache.
   - Simulates a real database with hardcoded data.

3. **Multithreading**:
   - Simulates concurrent product lookups using multiple threads.
   - Ensures thread safety when accessing the cache.

4. **Reusable Design**:
   - The LRU cache is generic and can be used for other key-value scenarios (e.g., caching query results).

---

## **Implementation Details**

### **1. LRU Cache**
The `LRUCache` class:
- Uses a **doubly linked list** to track the usage order of items.
- Uses a **hash map** for O(1) lookup, insertion, and deletion.
- Thread safety is ensured using a `std::mutex`.

### **2. Product Structure and Database**
The `Product` structure:
- Represents product details like ID, category, name, description, and a thumbnail image.

The `ProductDatabase` class:
- Simulates a thread-safe database with hardcoded product details.
- Provides methods to fetch product details by ID.

### **3. Product Cache**
The `ProductCache` class:
- First checks if a product is in the cache.
- If not found, fetches the product from the database and adds it to the cache.

### **4. Multithreading in Main Program**
The `main()` function:
- Simulates concurrent product lookups by multiple clients.
- Uses `std::thread` to demonstrate thread safety and cache efficiency.

---

## **File Structure**
```plaintext
.
├── CMakeLists.txt       # CMake configuration file for building the project
├── include/             # Header files
│   ├── LRUCache.h       # Implements the generic thread-safe LRU cache
│   ├── Product.h        # Defines the Product structure and database simulation
│   └── ProductCache.h   # Combines the database and cache functionality
├── src/                 # Source files (implementation)
│   └── main.cpp         # Main program to demonstrate the system
├── tests/               # Unit tests
│   ├── test_product_cache.cpp  # Unit tests for ProductCache
│   ├── test_lru_cache.cpp      # Unit tests for LRUCache
│   └── MockProductDatabase.h   # Mock database for testing
└── README.md            # This documentation file
```

## **Requirements**
- **C++ Compiler**: Requires a C++17 or later standard.
- **Threading**: Uses `std::thread` and requires the `-pthread` flag during compilation.
- **Google Test**: Used for unit tests.

---

## **Usage**

### **Compilation**
Use the following commands to build the project with CMake:

1 - Create a build directory and configure the project for compiling, linking and building:
```bash
mkdir build
cd build
cmake ..
```
2 - Compiles the project and generate the binaries:
```bash
make
```
This will generate the product_cache executable in the bin/ folder.
### **Execution**
Run the compiled program:
```bash
./bin/product_cache
```

### **Expected Output**
The program will simulate product lookups by multiple clients and output the results. For example:
```bash
Fetched Product: Laptop [ID: 1] <--- Fetched from Db
Fetched Product: Phone [ID: 2] <--- Fetched from Db
Fetched Product: Laptop [ID: 1] <--- Fetched from cache
```

### **Testing**
#### Unit Tests
Unit tests are available for both the ProductCache and LRUCache components.

To build and run the tests, use CMake as follows:

In the build directory (after comilation and building) Run the tests using:
```bash
ctest
```

This will run all the registered tests for ProductCache and LRUCache.

Alternatively, you can run individual test binaries:

```bash
./bin/test_product_cache  # Run tests for ProductCache
./bin/test_lru_cache      # Run tests for LRUCache
```

### Cleaning the Build

To clean up the generated build files (like compiled binaries and temporary files):
```bash
rm -rf build/*
```
This will remove all generated files from the build/ directory.