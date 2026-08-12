#pragma once

#include <stdexcept>

template <typename E>
class DLinkedList;

template <typename E>
class DNode {
public:
    E elem;
    DNode<E>* next;
    DNode<E>* prev;
    friend class DLinkedList<E>;
};

template <typename E>
class DLinkedList {
public:
    DLinkedList(); // constructor
    ~DLinkedList(); // destructor
    DLinkedList(const DLinkedList& other) = delete;
    DLinkedList& operator=(const DLinkedList& other) = delete;
    bool empty() const; // list empty?
    const E& front() const; // get reference to front element
    const E& back() const; // get reference to back element
    void addFront(const E& e); // add element to front of list
    DNode<E>* addFrontwRefReturn(const E& e); // add element to front of list
    void addBack(const E& e); // add element to back of list
    void removeFront(); // remove an element from front
    void removeBack(); // remove an element from back

    // public:
public:
    DNode<E>* header; // header sentinel
    DNode<E>* trailer; // trailer sentinel

    // protected:
public:
    void add(DNode<E>* v, const E& e); // insert new node before v
    void add(DNode<E>* v, DNode<E>* n); // insert new node before v
    DNode<E>* addwRefReturn(DNode<E>* v, const E& e); // insert new node before v
    void remove(DNode<E>* v); // remove the node v
    void removeWoDelete(DNode<E>* v); // remove the node v from DLL but dont delete it so that it stays on the heap
};

template <typename E>
DLinkedList<E>::DLinkedList()
{
    header = new DNode<E>;
    trailer = new DNode<E>;
    header->next = trailer;
    trailer->prev = header;
}

template <typename E>
DLinkedList<E>::~DLinkedList()
{
    while (!empty())
        removeFront();
    delete header;
    delete trailer;
}

template <typename E>
bool DLinkedList<E>::empty() const
{
    return header->next == trailer;
}

template <typename E>
const E& DLinkedList<E>::front() const
{
    if (empty())
        throw std::out_of_range("DLinkedList::front(): list is empty");
    return header->next->elem;
}

template <typename E>
const E& DLinkedList<E>::back() const
{
    if (empty())
        throw std::out_of_range("DLinkedList::back(): list is empty");
    return trailer->prev->elem;
}

template <typename E>
void DLinkedList<E>::add(DNode<E>* v, DNode<E>* n)
{
    if (v == n) {
        return;
    }
    n->next = v;
    n->prev = v->prev;
    v->prev->next = n;
    v->prev = n;
}

template <typename E>
void DLinkedList<E>::add(DNode<E>* v, const E& e)
{
    DNode<E>* u = new DNode<E>;
    u->elem = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
}

template <typename E>
DNode<E>* DLinkedList<E>::addwRefReturn(DNode<E>* v, const E& e)
{
    DNode<E>* u = new DNode<E>;
    u->elem = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
    return u;
}

template <typename E>
void DLinkedList<E>::remove(DNode<E>* v)
{
    DNode<E>* prev_node = v->prev;
    DNode<E>* next_node = v->next;
    prev_node->next = next_node;
    next_node->prev = prev_node;
    v->next = nullptr;
    v->prev = nullptr;
    delete v;
}

template <typename E>
void DLinkedList<E>::removeWoDelete(DNode<E>* v)
{
    DNode<E>* prev_node = v->prev;
    DNode<E>* next_node = v->next;
    prev_node->next = next_node;
    next_node->prev = prev_node;
    v->next = nullptr;
    v->prev = nullptr;
}

template <typename E>
void DLinkedList<E>::addFront(const E& e)
{
    add(header->next, e);
}

template <typename E>
DNode<E>* DLinkedList<E>::addFrontwRefReturn(const E& e)
{
    DNode<E>* nodeRefReturn = addwRefReturn(header->next, e);
    return nodeRefReturn;
}

template <typename E>
void DLinkedList<E>::addBack(const E& e)
{
    add(trailer, e);
}

template <typename E>
void DLinkedList<E>::removeFront()
{
    if (empty())
        throw std::underflow_error("DLinkedList::removeFront(): list is empty");
    remove(header->next);
}

template <typename E>
void DLinkedList<E>::removeBack()
{
    if (empty())
        throw std::underflow_error("DLinkedList::removeBack(): list is empty");
    remove(trailer->prev);
}