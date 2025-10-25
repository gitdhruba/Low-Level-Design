#include "./LinkedList.hpp"
#include "./Exception.hpp"
#include <new>

template class LinkedList<int, int>;

template <class K, class V>
LinkedList<K, V>::LinkedList() {
    try {
        this->head = new ListNode<K, V>();
        this->tail = new ListNode<K, V>();

        this->head->setNext(tail);
        this->tail->setPrev(head);
    }
    catch (const std::bad_alloc &e) {
        throw CacheException(std::string(e.what()));
    }
}

template <class K, class V>
LinkedList<K, V>::~LinkedList() {
    ListNode<K, V> *curr = head;
    while (curr != nullptr) {
        ListNode<K, V> *next = curr->getNext();
        delete curr;
        curr = next;
    }

    head = tail = nullptr;
}

template <class K, class V>
void LinkedList<K, V>::clear() {
    ListNode<K, V> *curr = head->getNext();
    while (curr != tail) {
        ListNode<K, V> *next = curr->getNext();
        delete curr;
        curr = next;
    }

    head->setNext(tail);
    tail->setPrev(head);
}

template <class K, class V>
void LinkedList<K, V>::push_front(ListNode<K, V> *node) {
    node->setNext(head->getNext());
    node->setPrev(head);
    head->getNext()->setPrev(node);
    head->setNext(node);
}

template <class K, class V>
void LinkedList<K, V>::push_back(ListNode<K, V> *node) {
    node->setNext(tail);
    node->setPrev(tail->getPrev());
    tail->getPrev()->setNext(node);
    tail->setPrev(node);
}

template <class K, class V>
bool LinkedList<K, V>::isEmpty() const {
    return (bool)(head->getNext() == tail);
}

template <class K, class V>
ListNode<K, V> * LinkedList<K, V>::pop_front() {
    if (isEmpty()) {
        std::string err = "[X] list empty";
        throw CacheException(err);
    }

    ListNode<K, V> *node = head->getNext();
    node->getNext()->setPrev(head);
    head->setNext(node->getNext());
    return node;
}

template <class K, class V>
ListNode<K, V> * LinkedList<K, V>::pop_back() {
    if (isEmpty()) {
        std::string err = "[X] list empty";
        throw CacheException(err);
    }

    ListNode<K, V> *node = tail->getPrev();
    node->getPrev()->setNext(tail);
    tail->setPrev(node->getPrev());
    return node;
}

template <class K, class V>
ListNode<K, V> * LinkedList<K, V>::remove_node(ListNode<K, V> *node) {
    if (isEmpty()) {
        std::string err = "[X] list empty";
        throw CacheException(err);
    }
    
    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());
    return node;
}