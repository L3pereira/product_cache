#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <unordered_map>
#include <list>
#include <mutex>
#include <optional>

// Generic LRU (Least Recently Used) Cache implementation
template<typename Key, typename Value>
class LRUCache {
private:
    size_t capacity; // Maximum number of items the cache can hold
    std::list<std::pair<Key, Value>> items; // Doubly linked list to maintain LRU order
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cache_map; // Hash map for O(1) access
    mutable std::mutex cache_mutex; // Mutex for thread safety

    // Moves an accessed item to the front of the list
    void moveToFront(typename std::list<std::pair<Key, Value>>::iterator it) {
        items.splice(items.begin(), items, it);
    }

public:
    // Constructor to initialize the cache with a fixed capacity
    explicit LRUCache(size_t max_size) : capacity(max_size) {}

    // Retrieves an item from the cache, if it exists
    std::optional<Value> get(const Key& key) {
        std::lock_guard<std::mutex> lock(cache_mutex);
        auto it = cache_map.find(key);
        if (it == cache_map.end()) {
            return std::nullopt; // Return empty if item is not found
        }
        moveToFront(it->second); // Mark as recently used
        return it->second->second; // Return the cached value
    }

    // Adds an item to the cache, evicting the least recently used item if necessary
    void put(const Key& key, const Value& value) {
        std::lock_guard<std::mutex> lock(cache_mutex);
        auto it = cache_map.find(key);

        // Update value if the key already exists
        if (it != cache_map.end()) {
            it->second->second = value;
            moveToFront(it->second);
            return;
        }

        // Evict the least recently used item if cache is full
        if (items.size() == capacity) {
            auto last = items.back();
            cache_map.erase(last.first);
            items.pop_back();
        }

        // Insert the new item at the front
        items.emplace_front(key, value);
        cache_map[key] = items.begin();
    }
};

#endif // LRUCACHE_H
