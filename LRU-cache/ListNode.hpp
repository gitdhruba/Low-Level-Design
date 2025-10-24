#ifndef LISTNODE_HDR
#define LISTNODE_HDR

template <class K, class V>
class ListNode {
private:
    K key;
    V value;
    ListNode<K, V> *prev, *next;

public:
    ListNode();
    ~ListNode();

    K getKey() const;
    V getValue() const;
    ListNode<K, V> * getPrev() const;
    ListNode<K, V> * getNext() const;

    void setKey(K);
    void setValue(V);
    void setPrev(ListNode<K, V> *);
    void setNext(ListNode<K, V> *);
};

#endif