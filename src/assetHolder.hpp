#pragma once

#include <map>
#include <memory>

#define SHARED std::shared_ptr
#define SHARED_MAKE(T, args...) std::make_shared<T>(args)
#define WEAK std::weak_ptr

// For cacheing assets. Makes it so level restarts and level transitions don't unload and reload unecessary stuff.
template <typename T>
struct AssetHolder
{
    std::map<std::string, WEAK<T>> cache;

    // Load an item.
    template<typename... Args>
    SHARED<T> Load(const std::string& key, Args&& ...args)
    {
        auto found = cache.find(key);
        if (found == cache.end() || found->second.expired())
        {
            auto ptr = SHARED_MAKE(T, std::forward<Args>(args)...);
            cache[key] = ptr;
            return ptr;
        }
        else return found->second.lock();
    }

};