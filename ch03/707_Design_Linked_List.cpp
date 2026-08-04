#include <iostream>
#include <utility>
#include <vector>

class Node {
    int val;
    Node* next;
    Node* prev;
    friend class MyLinkedList;
    Node()
        : val(0)
        , next(nullptr)
        , prev(nullptr)
    {
    }
};

class MyLinkedList {

private:
    int size;
    // header sentinel
    Node* header;
    // trailer sentinel
    Node* trailer;

public:
    MyLinkedList();
    ~MyLinkedList();
    bool empty() const;
    int get(int index);
    void addAtHead(int val);
    void addAtTail(int val);
    void addAtIndex(int index, int val);
    void deleteAtIndex(int index);

protected:
    void add(Node* v, int value); // insert new node before v
    void remove(Node* v); // remove the node v
};

MyLinkedList::MyLinkedList()
{
    header = new Node();
    trailer = new Node();
    header->next = trailer;
    trailer->prev = header;
    size = 0;
}

MyLinkedList::~MyLinkedList()
{
    while (!empty()) {
        remove(header->next);
    }
    delete header;
    delete trailer;
}

bool MyLinkedList::empty() const
{
    return header->next == trailer && size == 0;
}

void MyLinkedList::add(Node* v, int value)
{
    Node* u = new Node();
    u->val = value;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
    size++;
}

void MyLinkedList::remove(Node* v)
{
    Node* prev = v->prev;
    Node* next = v->next;
    prev->next = next;
    next->prev = prev;
    v->next = nullptr;
    v->prev = nullptr;
    delete v;
    size--;
}

int MyLinkedList::get(int index)
{
    if (index < 0 || empty() || index >= size) {
        return -1;
    }
    int stepCount = 0;
    Node* curr = header;
    while (stepCount <= index) {
        curr = curr->next;
        stepCount++;
    }
    return curr->val;
}

void MyLinkedList::addAtHead(int val)
{
    add(header->next, val);
}

void MyLinkedList::addAtTail(int val)
{
    add(trailer, val);
}

void MyLinkedList::addAtIndex(int index, int val)
{
    if (index < 0 || index > size) {
        return;
    }
    int stepCount = 0;
    Node* curr = header;
    while (stepCount <= index) {
        curr = curr->next;
        stepCount++;
    }
    add(curr, val);
    return;
}

void MyLinkedList::deleteAtIndex(int index)
{
    if (index < 0 || empty() || index >= size) {
        return;
    }
    int stepCount = 0;
    Node* curr = header;
    while (stepCount <= index) {
        curr = curr->next;
        stepCount++;
    }
    remove(curr);
    return;
}

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */

int main()
{
    MyLinkedList* mylinkedlist = new MyLinkedList();
    mylinkedlist->addAtHead(1);
    mylinkedlist->addAtTail(3);
    mylinkedlist->addAtIndex(1, 2);
    std::cout << mylinkedlist->get(1) << std::endl;
    mylinkedlist->deleteAtIndex(1);
    std::cout << mylinkedlist->get(1) << std::endl;
    return 0;
}