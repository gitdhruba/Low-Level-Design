#include "./LRUCache.hpp"
#include "./Exception.hpp"

template class LRUCache<int, int>;

template <class K, class V>
LRUCache<K, V>::LRUCache(int _size) 
    : maxSize(_size), size(0)
{
    hashMap.clear();
    list.clear();
}

template <class K, class V>
LRUCache<K, V>::~LRUCache() {
    hashMap.clear();
    list.clear();
}

template <class K, class V>
void LRUCache<K, V>::clear() {
    std::lock_guard<std::mutex> lock(mtx);
    hashMap.clear();
    list.clear();
}

template <class K, class V>
void LRUCache<K, V>::put(const K &key, const V &value) {
    std::lock_guard<std::mutex> lock(mtx);
    try {
        typename std::unordered_map<K, ListNode<K, V> *>::iterator it = hashMap.find(key);
        if ((it == hashMap.end()) || (it->second == nullptr)) {              // does not exist
            // if size exceeded
            if (size >= maxSize) {
                // remove LRU one
                ListNode<K, V> *evictedNode = list.pop_back();
                hashMap.erase(evictedNode->getKey());

                evictedNode->setKey(key);
                evictedNode->setValue(value);
                list.push_front(evictedNode);
                hashMap[key] = evictedNode;
            }
            // yet not full
            else {
                ListNode<K, V> *node = new ListNode<K, V>();
                node->setKey(key);
                node->setValue(value);
                list.push_front(node);
                hashMap[key] = node;
                size++;
            }
        }
        else {                                  // already exists
            ListNode<K, V> *node = it->second;
            list.remove_node(node);
            node->setValue(value);
            list.push_front(node);
        }
    }
    catch (const std::exception &e) {
        throw CacheException(std::string(e.what()));
    }
}

template <class K, class V>
V LRUCache<K, V>::get(const K &key) {
    std::lock_guard<std::mutex> lock(mtx);
    try {
        typename std::unordered_map<K, ListNode<K, V> *>::iterator it = hashMap.find(key);
        if ((it == hashMap.end()) || (it->second == nullptr)) {             // does not exist
            std::string msg = "miss";
            throw CacheException(msg);
        }
        else {                                                              // exists
            ListNode<K, V> *node = it->second;
            list.remove_node(node);
            list.push_front(node);
            return node->getValue();
        }
    }
    catch (const std::exception &e) {
        throw CacheException(std::string(e.what()));
    }
}