#include "../common/Circularly_Linked_List.hpp"
#include <iostream>

class MyCircularQueue : private CLinkedList<int> {
public:
    int maxSize;
    int size;

public:
    MyCircularQueue(int k)
        : maxSize(k)
        , size(0)
    {
    }

    ~MyCircularQueue()
    {
        CLinkedList<int>::~CLinkedList();
    }

    bool enQueue(int value)
    {
        if (size >= maxSize) {
            return false;
        }
        CLinkedList<int>::add(value);
        CLinkedList<int>::advance();
        size++;
        return true;
    }

    bool deQueue()
    {
        if (size <= 0) {
            return false;
        }
        try {
            CLinkedList<int>::remove();
            size--;
        } catch (const std::exception& e) {
            // std::cerr << e.what() << '\n';
            return false;
        }
        return true;
    }

    int Front()
    {
        if (CLinkedList<int>::empty()) {
            return -1;
        }
        return CLinkedList<int>::front();
    }

    int Rear()
    {
        if (CLinkedList<int>::empty()) {
            return -1;
        }
        return CLinkedList<int>::back();
    }

    bool isEmpty()
    {
        if (CLinkedList<int>::empty() && size == 0) {
            return true;
        }
        return false;
    }

    bool isFull()
    {
        if (size >= maxSize) {
            return true;
        }
        return false;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

int main()
{
    MyCircularQueue* CLLQueue = new MyCircularQueue(8);
    // std::cout << (CLLQueue->enQueue(1) ? "true" : "false") << std::endl;
    // std::cout << (CLLQueue->enQueue(2) ? "true" : "false") << std::endl;
    // std::cout << (CLLQueue->enQueue(3) ? "true" : "false") << std::endl;
    // std::cout << (CLLQueue->enQueue(4) ? "true" : "false") << std::endl;
    // std::cout << CLLQueue->Rear() << std::endl;
    // std::cout << (CLLQueue->isFull() ? "true" : "false") << std::endl;
    // std::cout << (CLLQueue->deQueue() ? "true" : "false") << std::endl;
    // std::cout << (CLLQueue->enQueue(4) ? "true" : "false") << std::endl;
    // std::cout << CLLQueue->Rear() << std::endl;
    std::cout << (CLLQueue->enQueue(3) ? "true" : "false") << std::endl;
    std::cout << (CLLQueue->enQueue(9) ? "true" : "false") << std::endl;
    std::cout << (CLLQueue->enQueue(5) ? "true" : "false") << std::endl;
    std::cout << (CLLQueue->enQueue(0) ? "true" : "false") << std::endl;
    std::cout << (CLLQueue->deQueue() ? "true" : "false") << std::endl;
    std::cout << (CLLQueue->deQueue() ? "true" : "false") << std::endl;
    std::cout << (CLLQueue->isEmpty() ? "true" : "false") << std::endl;
    std::cout << (CLLQueue->isEmpty() ? "true" : "false") << std::endl;
    std::cout << CLLQueue->Rear() << std::endl;
    std::cout << CLLQueue->Rear() << std::endl;
    std::cout << (CLLQueue->deQueue() ? "true" : "false") << std::endl;
    return 0;
}