#pragma once

#include <stdexcept>

template <typename E>
class DLinkedListwIterator {
private:
    class DNode {
    public:
        E elem;
        DNode* next;
        DNode* prev;
    };

public:
    class Iterator {
    public:
        E& operator*(); // returns a reference to the element
        bool operator==(const Iterator& p) const; // checks for equality in position
        bool operator!=(const Iterator& p) const; // checks for inequality in position
        Iterator& operator++(); // moves the iterator one position forward
        Iterator& operator--(); // moves the iterator one position backward
        friend class DLinkedListwIterator;

    private:
        DNode* v; // pointer to the node
        Iterator(DNode* u); // create iterator from node
    };

private: // data members
    int n; // number of items
    DNode* header; // header sentinel
    DNode* trailer; // trailer sentinel

public:
    DLinkedListwIterator(); // default constructor
    ~DLinkedListwIterator(); // destructor

    // ---- housekeeping (Rule of Five) ----
    // This class owns heap-allocated nodes via raw pointers and frees them
    // in its destructor, so the compiler-generated copy/move members (which
    // would just shallow-copy those pointers) are unsafe - two objects would
    // end up believing they each own the same nodes, and whichever one is
    // destroyed second would double-free. See the move constructor below
    // for a longer walkthrough of why the move operations in particular are
    // implemented the way they are.
    DLinkedListwIterator(const DLinkedListwIterator& other); // copy constructor
    DLinkedListwIterator& operator=(const DLinkedListwIterator& other); // copy assignment
    DLinkedListwIterator(DLinkedListwIterator&& other) noexcept; // move constructor
    DLinkedListwIterator& operator=(DLinkedListwIterator&& other) noexcept; // move assignment

    int size() const; // list size
    bool empty() const; // is the list empty
    Iterator begin() const; // beginning position
    Iterator end() const; // end (just beyond last) position
    void insert(const Iterator& p, const E& e); // insert e before iterator position p
    void insertFront(const E&); // insert at the front
    void insertBack(const E&); // insert at the rear
    void erase(const Iterator& p); // remove this node
    void eraseFront(); // remove first
    void eraseBack(); // remove last

private:
    void copyFrom(const DLinkedListwIterator& other); // deep-copy other's elements into *this
    void moveFrom(DLinkedListwIterator& other) noexcept; // steal other's nodes, leave other empty
    void clear(); // erase every element (sentinels stay)
};

// ALL ITERATOR METHODS
template <typename E>
DLinkedListwIterator<E>::Iterator::Iterator(DNode* u)
{
    v = u;
}

template <typename E>
E& DLinkedListwIterator<E>::Iterator::operator*()
{
    return v->elem;
}

template <typename E>
bool DLinkedListwIterator<E>::Iterator::operator==(const Iterator& p) const
{
    return v == p.v;
}

template <typename E>
bool DLinkedListwIterator<E>::Iterator::operator!=(const Iterator& p) const
{
    return v != p.v;
}

template <typename E>
typename DLinkedListwIterator<E>::Iterator& DLinkedListwIterator<E>::Iterator::operator++()
{
    v = v->next;
    return *this;
}

template <typename E>
typename DLinkedListwIterator<E>::Iterator& DLinkedListwIterator<E>::Iterator::operator--()
{
    v = v->prev;
    return *this;
}

// ALL DLINKEDLIST METHODS
template <typename E>
DLinkedListwIterator<E>::DLinkedListwIterator()
{
    n = 0;
    header = new DNode;
    trailer = new DNode;
    header->next = trailer;
    header->prev = nullptr;
    trailer->prev = header;
    trailer->next = nullptr;
}

template <typename E>
DLinkedListwIterator<E>::~DLinkedListwIterator()
{
    while (!empty()) {
        eraseBack();
    }
    delete header;
    delete trailer;
}

// ------------------------------------------------------------------------
// copyFrom / clear - shared helpers for the housekeeping methods below.
// ------------------------------------------------------------------------
// copyFrom walks `other` front-to-back and re-inserts each element, letting
// insertBack() do the actual node allocation and linking - that way the
// linking logic only has to live in one place. clear() empties *this down
// to just the two sentinels (used before a copy/move assignment replaces
// *this's contents).
template <typename E>
void DLinkedListwIterator<E>::copyFrom(const DLinkedListwIterator& other)
{
    for (DNode* cur = other.header->next; cur != other.trailer; cur = cur->next)
        insertBack(cur->elem);
}

template <typename E>
void DLinkedListwIterator<E>::clear()
{
    while (!empty())
        eraseBack();
}

// ------------------------------------------------------------------------
// Copy constructor / copy assignment
// ------------------------------------------------------------------------
// A "deep copy": build a brand new pair of sentinels for *this, then clone
// every element from `other` one at a time. *this and `other` end up as two
// fully independent lists - afterwards, modifying one can never affect the
// other, and each one's destructor only ever frees nodes it allocated
// itself.
template <typename E>
DLinkedListwIterator<E>::DLinkedListwIterator(const DLinkedListwIterator& other)
{
    n = 0;
    header = new DNode;
    trailer = new DNode;
    header->next = trailer;
    header->prev = nullptr;
    trailer->prev = header;
    trailer->next = nullptr;
    copyFrom(other);
}

template <typename E>
DLinkedListwIterator<E>& DLinkedListwIterator<E>::operator=(const DLinkedListwIterator& other)
{
    // Self-assignment guard: `x = x;` would otherwise clear() *this and
    // then try to copyFrom() a list it just emptied - always check this
    // first in an assignment operator that manages a resource.
    if (this == &other)
        return *this;
    clear();
    copyFrom(other);
    return *this;
}

// ------------------------------------------------------------------------
// Move constructor
// ------------------------------------------------------------------------
// Quick primer for the "rvalue"/"move" terminology, since this is the
// first place in this file it comes up:
//
// An rvalue is (loosely) a temporary value with no name of its own, about
// to be destroyed - the return value of a function, or anything explicitly
// wrapped in std::move(). For example:
//
//     DLinkedListwIterator<int> makeList()
//     {
//         DLinkedListwIterator<int> tmp;
//         tmp.insertBack(1);
//         tmp.insertBack(2);
//         return tmp;                     // `tmp` is about to be destroyed
//     }                                   // -> it's returned as an rvalue
//
//     DLinkedListwIterator<int> a = makeList();       // move ctor runs
//     DLinkedListwIterator<int> b = std::move(a);     // move ctor runs too
//
// std::move() doesn't actually move anything by itself - all it does is
// cast its argument to an rvalue reference (E&&) so that overload
// resolution picks THIS constructor instead of the copy constructor above.
// It's really just an honest way of saying "I no longer need this value,
// you're free to gut it."
//
// Why bother? Because `other` is either a genuine temporary or something
// the caller has explicitly given up on - so unlike the copy constructor,
// we don't need to clone every node. We can just steal `other`'s
// header/trailer pointers directly: an O(1) pointer swap, instead of the
// copy constructor's O(n) walk-and-clone of every element.
//
// The one thing we must not skip: `other` is a real object and its
// destructor WILL still run at the end of its scope. If we stole its
// header/trailer without giving it fresh ones of its own, both `other` and
// *this would believe they own the same nodes, and whichever destructor
// runs second would double-free them - the exact bug this file's own
// housekeeping is here to prevent. So moveFrom() always leaves `other`
// as a valid, empty, independently-destructible list.
template <typename E>
DLinkedListwIterator<E>::DLinkedListwIterator(DLinkedListwIterator&& other) noexcept
{
    moveFrom(other);
}

// ------------------------------------------------------------------------
// Move assignment
// ------------------------------------------------------------------------
// Same idea as the move constructor, but *this already owns nodes of its
// own that need freeing first: clear() the elements, delete *this's own
// two sentinels (moveFrom() is about to overwrite header/trailer with
// other's), then steal other's nodes exactly as the move constructor does.
template <typename E>
DLinkedListwIterator<E>& DLinkedListwIterator<E>::operator=(DLinkedListwIterator&& other) noexcept
{
    if (this == &other)
        return *this;
    clear();
    delete header;
    delete trailer;
    moveFrom(other);
    return *this;
}

template <typename E>
void DLinkedListwIterator<E>::moveFrom(DLinkedListwIterator& other) noexcept
{
    n = other.n;
    header = other.header;
    trailer = other.trailer;

    // Leave `other` in a valid, empty state of its own - its destructor is
    // still going to run, and it must not touch the nodes we just took.
    // (Strictly speaking `new` below could throw, which would technically
    // violate `noexcept` - the same simplification the default constructor
    // above already makes. A production container would avoid allocating
    // sentinels at all for this reason; not worth the extra complexity here.)
    other.n = 0;
    other.header = new DNode;
    other.trailer = new DNode;
    other.header->next = other.trailer;
    other.header->prev = nullptr;
    other.trailer->prev = other.header;
    other.trailer->next = nullptr;
}

template <typename E>
int DLinkedListwIterator<E>::size() const
{
    return n;
}

template <typename E>
bool DLinkedListwIterator<E>::empty() const
{
    return n == 0;
}

template <typename E>
typename DLinkedListwIterator<E>::Iterator DLinkedListwIterator<E>::begin() const
{
    return Iterator(header->next);
}

template <typename E>
typename DLinkedListwIterator<E>::Iterator DLinkedListwIterator<E>::end() const
{
    return Iterator(trailer);
}

template <typename E>
void DLinkedListwIterator<E>::insert(const Iterator& p, const E& e)
{
    DNode* w = p.v; // p's node
    DNode* u = w->prev; // p's predecessor
    DNode* v = new DNode; // the new DNode to store
    v->elem = e;
    v->next = w;
    v->prev = u;
    w->prev = v;
    u->next = v;
    n++;
}

template <typename E>
void DLinkedListwIterator<E>::insertFront(const E& e)
{
    insert(begin(), e);
}

template <typename E>
void DLinkedListwIterator<E>::insertBack(const E& e)
{
    insert(end(), e);
}

template <typename E>
void DLinkedListwIterator<E>::erase(const Iterator& p)
{
    DNode* v = p.v; // node to delete
    DNode* u = v->prev; // predecessor
    DNode* w = v->next; // successor
    u->next = w;
    w->prev = u;
    delete v;
    n--;
}

template <typename E>
void DLinkedListwIterator<E>::eraseFront()
{
    if (empty())
        throw std::underflow_error("DLinkedListwIterator::eraseFront(): list is empty");
    erase(begin());
}

template <typename E>
void DLinkedListwIterator<E>::eraseBack()
{
    if (empty())
        throw std::underflow_error("DLinkedListwIterator::eraseBack(): list is empty");
    erase(--end());
}
