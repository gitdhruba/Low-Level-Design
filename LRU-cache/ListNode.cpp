#include "./ListNode.hpp"

template class ListNode<int, int>;

template<class K, class V>
ListNode<K, V>::ListNode()
    : key(K{}), value(V{}), prev(nullptr), next(nullptr) {}

template<class K, class V>
ListNode<K, V>::~ListNode() {}

template<class K, class V>
K ListNode<K, V>::getKey() const {
    return this->key;
}

template<class K, class V>
V ListNode<K, V>::getValue() const {
    return this->value;
}

template<class K, class V>
ListNode<K, V> * ListNode<K, V>::getPrev() const {
    return this->prev;
}

template<class K, class V>
ListNode<K, V> * ListNode<K, V>::getNext() const {
    return this->next;
}

template<class K, class V>
void ListNode<K, V>::setKey(K key) {
    this->key = key;
}

template<class K, class V>
void ListNode<K, V>::setValue(V val) {
    this->value = val;
}

template<class K, class V>
void ListNode<K, V>::setPrev(ListNode<K, V> *prev) {
    this->prev = prev;
}

template<class K, class V>
void ListNode<K, V>::setNext(ListNode<K, V> *next) {
    this->next = next;
}