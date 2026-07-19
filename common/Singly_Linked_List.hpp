#pragma once

#include <stdexcept>

template <typename E>
class SLinkedList;

template <typename E>
class SNode {
public:
    E elem;
    SNode<E>* next;
    friend class SLinkedList<E>;
};

template <typename E>
class SLinkedList {
public:
    // methods:
    SLinkedList();
    ~SLinkedList();
    bool empty() const;
    const E& front() const;
    void addFront(const E& e);
    void removeFront();
    SNode<E>* find(const E& e);
    template <typename KeyEqual>
    SNode<E>* find(const E& e, KeyEqual eq);
    bool contains(const E& e);
    template <typename KeyEqual>
    bool contains(const E& e, KeyEqual eq); // new overload
    void remove(SNode<E>* v); // remove the node v

private:
    SNode<E>* head;
};

template <typename E>
void SLinkedList<E>::remove(SNode<E>* v)
{
    if (v == nullptr || head == nullptr)
        return;

    if (head == v) {
        head = head->next;
        delete v;
        return;
    }

    SNode<E>* rear = head;
    SNode<E>* fwd = head->next;
    while (fwd != nullptr && fwd != v) {
        rear = rear->next;
        fwd = fwd->next;
    }
    if (fwd == nullptr) {
        return;
    }
    rear->next = fwd->next;
    delete fwd;
}

template <typename E>
template <typename KeyEqual>
SNode<E>* SLinkedList<E>::find(const E& e, KeyEqual eq)
{
    if (empty())
        return nullptr;

    SNode<E>* res = head;
    while (res != nullptr) {
        if (eq(res->elem, e)) {
            return res;
        }
        res = res->next;
    }
    return nullptr;
}

template <typename E>
SNode<E>* SLinkedList<E>::find(const E& e)
{
    if (empty())
        return nullptr;

    SNode<E>* res = head;
    while (res != nullptr) {
        if (res->elem == e) {
            return res;
        }
        res = res->next;
    }
    return nullptr;
}

template <typename E>
template <typename KeyEqual>
bool SLinkedList<E>::contains(const E& e, KeyEqual eq)
{
    if (empty())
        return false;

    SNode<E>* curr = head;
    while (curr != nullptr) {
        if (eq(curr->elem, e)) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template <typename E>
bool SLinkedList<E>::contains(const E& e)
{
    if (empty())
        return false;

    SNode<E>* curr = head;
    while (curr != nullptr) {
        if (curr->elem == e) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

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
