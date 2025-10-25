#ifndef LRU_HDR
#define LRU_HDR

#include <mutex>
#include <unordered_map>
#include "./Cache.hpp"
#include "./LinkedList.hpp"

template <class K, class V>
class LRUCache : public ICache<K, V> {
private:
    const int maxSize;
    int size;
    std::unordered_map<K, ListNode<K, V> *> hashMap;
    LinkedList<K, V> list;
    std::mutex mtx;

public:
    LRUCache(int);
    virtual ~LRUCache();

    void clear() override;
    void put(const K &, const V &) override;
    V get(const K &) override;
};

#endif  