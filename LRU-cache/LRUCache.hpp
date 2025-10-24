#ifndef LRU_HDR
#define LRU_HDR

#include <unordered_map>
#include "./Cache.hpp"
#include "./LinkedList.hpp"

template <class K, class V>
class LRUCache : public ICache<K, V> {
private:
    int size;
    std::unordered_map<K, V> hashMap;
    LinkedList<K, V> availList, list;

public:
    LRUCache(int);
    virtual ~LRUCache();

    void put(K, V) override;
    V get(K) override;
};

#endif