#ifndef CACHE_HDR
#define CACHE_HDR

template <class K, class V>
class ICache {
public:
    ICache() {}
    virtual ~ICache() {}

    virtual void clear() = 0;
    virtual void put(const K &, const V &) = 0;
    virtual V get(const K &) = 0;
};

#endif