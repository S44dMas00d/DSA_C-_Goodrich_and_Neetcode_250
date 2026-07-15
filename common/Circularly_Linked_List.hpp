#pragma once

#include <stdexcept>

template <typename E>
class CLinkedList;

template <typename E>
class CNode {
    E elem;
    CNode<E>* next;
    friend class CLinkedList<E>;
};

template <typename E>
class CLinkedList {
public:
    CLinkedList(); // constructor
    ~CLinkedList(); // destructor
    CLinkedList(const CLinkedList& other) = delete;
    CLinkedList& operator=(const CLinkedList& other) = delete;
    bool empty() const; // list empty?
    const E& front() const; // element at cursor
    const E& back() const; // element following cursor
    void advance(); // advance the cursor
    void add(const E& e); // add after cursor
    void remove(); // remove node after cursor
private:
    CNode<E>* cursor; // the cursor pointer to a node
};

template <typename E>
CLinkedList<E>::CLinkedList()
    : cursor(nullptr)
{
}

template <typename E>
CLinkedList<E>::~CLinkedList()
{
    while (!empty())
        remove();
}

template <typename E>
bool CLinkedList<E>::empty() const
{
    return cursor == nullptr;
}

template <typename E>
const E& CLinkedList<E>::front() const
{
    if (empty())
        throw std::out_of_range("CLinkedList::front(): list is empty");
    return cursor->next->elem;
}

template <typename E>
const E& CLinkedList<E>::back() const
{
    if (empty())
        throw std::out_of_range("CLinkedList::back(): list is empty");
    return cursor->elem;
}

template <typename E>
void CLinkedList<E>::advance()
{
    if (empty())
        throw std::out_of_range("CLinkedList::advance(): list is empty");
    cursor = cursor->next;
}

template <typename E>
void CLinkedList<E>::add(const E& e)
{
    CNode<E>* v = new CNode<E>;
    v->elem = e;
    if (cursor == nullptr) {
        v->next = v;
        cursor = v;
    } else {
        v->next = cursor->next;
        cursor->next = v;
    }
}

template <typename E>
void CLinkedList<E>::remove()
{
    if (empty())
        throw std::out_of_range("CLinkedList::remove(): list is empty");
    CNode<E>* old = cursor->next;
    if (old == cursor) {
        cursor = nullptr;
    } else {
        cursor->next = old->next;
    }
    delete old;
}
