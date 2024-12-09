#ifndef INMEMORYCACHE_H
#define INMEMORYCACHE_H

#include "icache.h"
#include "product.h"
#include <unordered_map>
#include <optional>

// Simple in-memory cache implementation for testing
template <typename Key, typename Value>
class MockLRUCache : public ICache<Key, Value>
{
public:
    // Return the product associated with the key, if found
    std::optional<Value> get(const Key &key) override
    {
        auto it = _cache.find(key);
        if (it != _cache.end())
        {
            return it->second; // Found in cache
        }
        return std::nullopt; // Not found in cache
    }

    // Insert a product into the cache
    void put(const Key &key, const Value &value) override
    {
        _cache[key] = value;
    }

    // Optional: evict a product (e.g., to simulate cache eviction behavior)
    void evict()
    {
        if (!_cache.empty())
        {
            _cache.erase(_cache.begin()); // Simple eviction strategy (remove the first item)
        }
    }

private:
    mutable std::unordered_map<Key, Value> _cache; // Cache data
};

#endif // INMEMORYCACHE_H
