#pragma once

#include "Doubly_Linked_List.hpp"
#include <iostream>
#include <stdexcept>

// an interface for a queue
template <typename E>
class QueuewDLL {
public:
    QueuewDLL();
    ~QueuewDLL();
    int size() const; // number of items in queue
    bool empty() const; // is the queue empty?
    const E& front(); // the front element
    void enqueue(const E& e); // enqueue element at rear
    void dequeue(); // dequeue element at front

private:
    DLinkedList<E> DLL;
    int n;
};

template <typename E>
QueuewDLL<E>::QueuewDLL()
    : DLL()
    , n(0)
{
}

template <typename E>
QueuewDLL<E>::~QueuewDLL() { }

template <typename E>
int QueuewDLL<E>::size() const
{
    return n;
}

template <typename E>
bool QueuewDLL<E>::empty() const
{
    return n == 0;
}

template <typename E>
const E& QueuewDLL<E>::front()
{
    if (empty()) {
        throw std::runtime_error("queue is empty");
    }
    return DLL.front();
}

template <typename E>
void QueuewDLL<E>::enqueue(const E& e)
{
    DLL.addBack(e);
    n++;
}

template <typename E>
void QueuewDLL<E>::dequeue()
{
    DLL.removeFront();
    n--;
}
