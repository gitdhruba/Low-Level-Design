#ifndef CACHE_HDR
#define CACHE_HDR

template <class K, class V>
class ICache {
public:
    ICache() {}
    virtual ~ICache() {}

    virtual void put(K, V) = 0;
    virtual V get(K) = 0;
};

#endif