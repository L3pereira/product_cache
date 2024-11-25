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
├── LRUCache.h         # Implements the generic thread-safe LRU cache
├── Product.h          # Defines the Product structure and database simulation
├── ProductCache.h     # Combines the database and cache functionality
├── main.cpp           # Main program to demonstrate the system
└── README.md          # This documentation file
```

## **Requirements**
- **C++ Compiler**: Requires a C++17 or later standard.
- **Threading**: Uses `std::thread` and requires the `-pthread` flag during compilation.

---

## **Usage**

### **Compilation**
Use the following command to compile the program:
```bash
g++ -std=c++20 -pthread main.cpp -o product_cache
```

### **Execution**
Run the compiled program:
```bash
./product_cache
```

### **Expected Output**
The program will simulate product lookups by multiple clients and output the results. For example:
```bash
Fetched Product: Laptop [ID: 1] <--- Fetched from Db
Fetched Product: Phone [ID: 2] <--- Fetched from Db
Fetched Product: Laptop [ID: 1] <--- Fetched from cache
```


