#ifndef LRUCACHE_H
#define LRUCACHE_H

#include "icache.h"
#include <unordered_map>
#include <list>
#include <optional>

// Generic LRU (Least Recently Used) Cache implementation
template <typename Key, typename Value>
class LRUCache : public ICache<Key, Value>
{
private:
    size_t _capacity;                                                                        // Maximum number of items the cache can hold
    std::list<std::pair<Key, Value>> _items;                                                 // Doubly linked list to maintain LRU order
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> _cache_map; // Hash map for O(1) access

    // Moves an accessed item to the front of the list
    void _moveToFront(typename std::list<std::pair<Key, Value>>::iterator it)
    {
        _items.splice(_items.begin(), _items, it);
    }

public:
    // Constructor to initialize the cache with a fixed capacity
    explicit LRUCache(size_t max_size) : _capacity(max_size) {}

    // Retrieves an item from the cache, if it exists
    std::optional<Value> get(const Key &key) override
    {
        auto it = _cache_map.find(key);
        if (it == _cache_map.end())
        {
            return std::nullopt; // Return empty if item is not found
        }
        _moveToFront(it->second);  // Mark as recently used
        return it->second->second; // Return the cached value
    }

    // Adds an item to the cache, evicting the least recently used item if necessary
    void put(const Key &key, const Value &value) override
    {
        auto it = _cache_map.find(key);

        // Update value if the key already exists
        if (it != _cache_map.end())
        {
            it->second->second = value;
            _moveToFront(it->second);
            return;
        }

        // Evict the least recently used item if cache is full
        if (_items.size() == _capacity)
        {
            auto last = _items.back();
            _cache_map.erase(last.first);
            _items.pop_back();
        }

        // Insert the new item at the front
        _items.emplace_front(key, value);
        _cache_map[key] = _items.begin();
    }
};

#endif // LRUCACHE_H
