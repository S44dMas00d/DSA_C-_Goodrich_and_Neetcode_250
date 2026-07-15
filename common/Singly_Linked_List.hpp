#pragma once

#include <stdexcept>

template <typename E>
class SLinkedList;

template <typename E>
class SNode {
private:
    E elem;
    SNode<E>* next;
    friend class SLinkedList<E>;
};

template <typename E>
class SLinkedList {
public:
    SLinkedList();
    ~SLinkedList();
    bool empty() const;
    const E& front() const;
    void addFront(const E& e);
    void removeFront();

private:
    SNode<E>* head;
};

template <typename E>
SLinkedList<E>::SLinkedList()
    : head(nullptr)
{
}

template <typename E>
SLinkedList<E>::~SLinkedList()
{
    while (!empty())
        removeFront();
}

template <typename E>
bool SLinkedList<E>::empty() const
{
    return head == nullptr;
}

template <typename E>
const E& SLinkedList<E>::front() const
{
    if (empty())
        throw std::out_of_range("SLinkedList::front(): list is empty");
    return head->elem;
}

template <typename E>
void SLinkedList<E>::addFront(const E& e)
{
    SNode<E>* v = new SNode<E>;
    v->elem = e;
    v->next = head;
    head = v;
}

template <typename E>
void SLinkedList<E>::removeFront()
{
    if (empty())
        throw std::underflow_error("SLinkedList::removeFront(): list is empty");
    SNode<E>* old = head;
    head = old->next;
    delete old;
}
