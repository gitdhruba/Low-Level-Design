#ifndef DLL_HDR

#define DLL_HDR

#include "./ListNode.hpp"
#include <memory>

template <class K, class V>
class LinkedList {
private:
    ListNode<K, V> *head, *tail;

public:
    LinkedList();
    ~LinkedList();

    void clear();
    void push_front(ListNode<K, V> *);
    void push_back(ListNode<K, V> *);
    ListNode<K, V> * pop_front();
    ListNode<K, V> * pop_back();

    bool isEmpty() const;

    ListNode<K, V> * remove_node(ListNode<K, V> *);
};

#endif