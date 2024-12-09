#ifndef ICACHE_H
#define ICACHE_H

#include <optional>

template <typename Key, typename Value>
class ICache
{
public:
    virtual ~ICache() = default;

    // Retrieves an item from the cache
    virtual std::optional<Value> get(const Key &key) = 0;

    // Adds an item to the cache
    virtual void put(const Key &key, const Value &value) = 0;
};

#endif // ICACHE_H
