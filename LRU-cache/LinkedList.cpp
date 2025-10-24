#include "./LinkedList.hpp"

template <class K, class V>
LinkedList<K, V>::LinkedList() {
    this->head = new ListNode<K, V>>();
    this->tail = new ListNode<K, V>();

    this->head->setNext(tail);
    this->tail->setPrev(head);
}

template <class K, class V>
LinkedList<K, V>::~LinkedList() {
    LinkedList<K, V> *curr = head, *next = head->getNext();
    while (curr != nullptr) {
        delete curr;
        curr = next;
        next = next->getNext();
    }
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
ListNode<K, V> * LinkedList<K, V>::pop_front() {
    ListNode<K, V> *node = head->getNext();
    node->getNext()->setPrev(head);
    head->setNext(node->getNext());
    return node;
}

template <class K, class V>
ListNode<K, V> * LinkedList<K, V>::pop_back() {
    ListNode<K, V> *node = tail->getPrev();
    node->getPrev()->setNext(tail);
    tail->setPrev(node->getPrev());
    return node;
}

template <class K, class V>
bool LinkedList<K, V>::isEmpty() const {
    return (bool)(head->getNext() != tail);
}

template <class K, class V>
ListNode<K, V> * LinkedList<K, V>::remove_node(ListNode<K, V> *node) {
    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());
    return node;
}