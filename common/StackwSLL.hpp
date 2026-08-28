#pragma once

#include "Singly_Linked_List.hpp"
#include <iostream>
#include <stdexcept>

template <typename E>
class StackwSLL {
public:
    StackwSLL(); // constructor
    int size() const; // number of items in the stack
    bool empty() const; // is the stack empty?
    const E& top() const; // the top element
    void push(const E& e); // push element onto stack
    void pop(); // pop the stack
private:
    SLinkedList<E> SLL;
    int n;
};

template <typename E>
StackwSLL<E>::StackwSLL()
    : SLL(SLinkedList<E>())
    , n(0)
{
}

template <typename E>
int StackwSLL<E>::size() const
{
    return n;
}

template <typename E>
bool StackwSLL<E>::empty() const
{
    return (n == 0);
}

template <typename E>
const E& StackwSLL<E>::top() const
{
    if (empty()) {
        throw std::runtime_error("stack is empty");
    }
    return SLL.front();
}

template <typename E>
void StackwSLL<E>::push(const E& e)
{
    ++n;
    SLL.addFront(e);
}

template <typename E>
void StackwSLL<E>::pop()
{
    if (empty()) {
        throw std::runtime_error("stack is empty");
    }

    --n;
    SLL.removeFront();
}
