#pragma once
#include "Dict_w_Binary_Search_Tree.hpp"
#include <algorithm> // std::max

// NonexistentElement is already declared by Dict_w_Binary_Search_Tree.hpp --
// reusing it here (rather than redefining it) is what let AVLTreeDict::erase
// throw the same type SearchTreeDict::erase does.

template <typename E>
class AVLTreeDict; // forward declaration so AVLEntry can name it as a friend

template <typename E>
class AVLEntry : public E {
private:
    int _ht;

protected:
    using K = typename E::Key;
    using V = typename E::Value;
    int height() const { return _ht; }
    void setHeight(int h) { _ht = h; }

public:
    AVLEntry(const K& k = K(), const V& v = V())
        : E(k, v)
        , _ht(0)
    {
    }
    friend class AVLTreeDict<E>;
};

template <typename E>
class AVLTreeDict : public SearchTreeDict<AVLEntry<E>> {
public:
    // Named AVLE, not AVLEntry -- reusing the class template's own name
    // ("using AVLEntry = AVLEntry<E>;") is a self-shadowing declaration
    // GCC rejects.
    using AVLE = AVLEntry<E>;
    using Iterator = typename SearchTreeDict<AVLE>::Iterator;

protected:
    using K = typename AVLE::Key;
    using V = typename AVLE::Value;
    using ST = SearchTreeDict<AVLE>;
    using TPos = typename ST::TPos;

public:
    AVLTreeDict();
    Iterator insert(const K& k, const V& x);
    void erase(const K& k);
    void erase(const Iterator& it);

protected:
    int height(const TPos& v) const;
    void setHeight(TPos v);
    bool isBalanced(const TPos& v) const;
    TPos tallGrandchild(const TPos& v) const;
    void rebalance(const TPos& v);
};

template <typename E>
AVLTreeDict<E>::AVLTreeDict()
    : ST()
{
}

template <typename E>
AVLTreeDict<E>::Iterator
AVLTreeDict<E>::insert(const K& k, const V& x)
{
    // finder/inserter/eraser/restructure/root/end are members of the
    // *dependent* base SearchTreeDict<AVLEntry> -- unqualified lookup
    // doesn't search dependent bases in a template, so each call needs the
    // `ST::` qualification to be found. (AVLTreeDict's own members --
    // setHeight, rebalance, ... -- don't need this.)
    TPos v = ST::inserter(k, x);
    setHeight(v);
    rebalance(v);
    return Iterator(v);
}

template <typename E>
void AVLTreeDict<E>::erase(const K& k)
{
    TPos v = ST::finder(k, ST::root());
    if (v.isExternal()) {
        throw NonexistentElement("Cant erase non existent key");
    }
    TPos w = ST::eraser(v);
    rebalance(w);
}

template <typename E>
void AVLTreeDict<E>::erase(const Iterator& it)
{
    // NOTE: it.getPosUnderIterator() by itself, passed to erase(...), would
    // implicitly convert back to an Iterator and call *this* overload again
    // (name hiding: declaring erase() here hides SearchTreeDict's erase()
    // overloads, so overload resolution never even considers them) --
    // infinite recursion. Go through eraser() directly instead, exactly
    // like erase(const K&) above, so we get back the position to rebalance
    // from.
    TPos v = it.getPosUnderIterator();
    TPos w = ST::eraser(v);
    rebalance(w);
}

template <typename E>
int AVLTreeDict<E>::height(const TPos& v) const
{
    return (v.isExternal() ? 0 : v->height());
}

template <typename E>
void AVLTreeDict<E>::setHeight(TPos v)
{
    int hl = height(v.left());
    int hr = height(v.right());
    v->setHeight(1 + std::max(hl, hr));
}

template <typename E>
bool AVLTreeDict<E>::isBalanced(const TPos& v) const
{
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
}

template <typename E>
AVLTreeDict<E>::TPos
AVLTreeDict<E>::tallGrandchild(const TPos& z) const
{
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr)) {
        if (height(zl.left()) >= height(zl.right())) {
            return zl.left();
        } else {
            return zl.right();
        }
    } else {
        if (height(zr.right()) >= height(zr.left())) {
            return zr.right();
        } else {
            return zr.left();
        }
    }
}

template <typename E>
void AVLTreeDict<E>::rebalance(const TPos& v)
{
    TPos z = v;
    while (!(z == ST::root())) {
        z = z.parent();
        setHeight(z);
        if (!isBalanced(z)) {
            TPos x = tallGrandchild(z);
            z = ST::restructure(x);
            setHeight(z.left());
            setHeight(z.right());
            setHeight(z);
        }
    }
}