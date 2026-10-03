#pragma once
#include "Linked_Binary_Tree.hpp"
#include <stdexcept>

// Thrown by erase(key) when the key is not present in the dictionary.
class NonexistentElement : public std::runtime_error {
public:
    explicit NonexistentElement(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

template <typename K, typename V>
class Entry {
public:
    using Key = K;
    using Value = V;

public:
    Entry(const K& k = K(), const V& v = V())
        : _key(k)
        , _value(v)
    {
    }
    const K& key() const
    {
        return _key;
    }
    const V& value() const
    {
        return _value;
    }
    void setKey(const K& key)
    {
        _key = key;
    }
    void setValue(const V& value)
    {
        _value = value;
    }

private:
    K _key;
    V _value;
};

template <typename E>
class SearchTreeDict {
public:
    using K = typename E::Key;
    using V = typename E::Value;
    class Iterator;

public:
    SearchTreeDict();
    int size() const;
    bool empty() const;
    Iterator find(const K& k);
    Iterator insert(const K& k, const V& v);
    void erase(const K& k);
    void erase(const Iterator& p);
    Iterator begin();
    Iterator end();

protected:
    using BinaryTree = LinkedBinaryTree<E>;
    using TPos = typename BinaryTree::Position;
    TPos root() const;
    TPos finder(const K& k, const TPos& v);
    TPos inserter(const K& k, const V& x);
    TPos eraser(TPos& v);
    TPos restructure(const TPos& v);

private:
    BinaryTree T;
    int n;

public:
    class Iterator {
    private:
        TPos v;

    public:
        Iterator(const TPos& vv)
            : v(vv)
        {
        }
        TPos getPosUnderIterator() const
        {
            return v;
        }
        const E& operator*() const { return *v; }
        E& operator*() { return *v; }
        bool operator==(const Iterator& p) const
        {
            return v == p.v;
        }
        Iterator& operator++();
        friend class SearchTreeDict;
    };
};

template <typename E>
SearchTreeDict<E>::Iterator&
SearchTreeDict<E>::Iterator::operator++()
{
    TPos w = v.right();
    if (w.isInternal()) {
        do {
            v = w;
            w = w.left();
        } while (w.isInternal());
    } else {
        w = v.parent();
        while (v == w.right()) {
            v = w;
            w = w.parent();
        }
        v = w;
    }
    return *this;
}

template <typename E>
SearchTreeDict<E>::SearchTreeDict()
    : T()
    , n(0)
{
    T.addRoot();
    T.expandExternal(T.root());
}

template <typename E>
int SearchTreeDict<E>::size() const
{
    return n;
}

template <typename E>
bool SearchTreeDict<E>::empty() const
{
    return n == 0;
}

template <typename E>
SearchTreeDict<E>::TPos SearchTreeDict<E>::root() const
{
    return T.root().left();
}

template <typename E>
SearchTreeDict<E>::Iterator
SearchTreeDict<E>::begin()
{
    TPos v = root();
    while (!v.isExternal()) {
        v = v.left();
    }
    return Iterator(v.parent());
}

template <typename E>
SearchTreeDict<E>::Iterator
SearchTreeDict<E>::end()
{
    return Iterator(T.root());
}

template <typename E>
SearchTreeDict<E>::TPos
SearchTreeDict<E>::finder(const K& k, const TPos& v)
{
    if (v.isExternal()) {
        return v;
    }
    if (k < v->key()) {
        return finder(k, v.left());
    } else if (k > v->key()) {
        return finder(k, v.right());
    } else {
        return v;
    }
}

template <typename E>
SearchTreeDict<E>::Iterator
SearchTreeDict<E>::find(const K& k)
{
    TPos v = finder(k, root());
    if (!v.isExternal()) {
        return Iterator(v);
    } else {
        return end();
    }
}

template <typename E>
SearchTreeDict<E>::TPos
SearchTreeDict<E>::inserter(const K& k, const V& x)
{
    TPos v = finder(k, root());
    while (!v.isExternal()) {
        v = finder(k, v.right());
    }
    T.expandExternal(v);
    v->setKey(k);
    v->setValue(x);
    n++;
    return v;
}

template <typename E>
SearchTreeDict<E>::Iterator
SearchTreeDict<E>::insert(const K& k, const V& x)
{
    TPos v = inserter(k, x);
    return Iterator(v);
}

template <typename E>
SearchTreeDict<E>::TPos
SearchTreeDict<E>::eraser(TPos& v)
{
    TPos w;
    if (v.left().isExternal())
        w = v.left();
    else if (v.right().isExternal())
        w = v.right();
    else {
        w = v.right();
        do {
            w = w.left();
        } while (!w.isExternal());
        TPos u = w.parent();
        v->setKey(u->key());
        v->setValue(u->value());
    }
    n--;
    return T.removeAboveExternal(w);
}

template <typename E>
void SearchTreeDict<E>::erase(const K& k)
{
    TPos v = finder(k, root());
    if (v.isExternal())
        throw NonexistentElement("Erase of nonexistent");
    eraser(v);
}

template <typename E>
void SearchTreeDict<E>::erase(const Iterator& p)
{
    TPos v = p.v; // eraser() mutates its argument, so work on a local copy
    eraser(v);
}

template <typename E>
SearchTreeDict<E>::TPos
SearchTreeDict<E>::restructure(const TPos& v)
{
    // Suppose you inserted an element - reference the example in Figure 10.9)
    // in the book on page 441 - say you inserted node 54, then the 54 node is w
    // w's parent is x, x's parent is y and y's parent is z. Now with that said,
    // we can see in the same figure node 62 gets promoted which is inline with
    // what the algorithm does for the double rotation shape we see in the figure,
    // i.e., we promote x for the zig-zag type form.

    // Most important is that if you inserted a node w, then according to figure
    // 10.9 - its parent x is where you start your restructure(x) function.

    // In removal however, figure 10.11 shows that you want to mark the parent of
    // removed node w as the z node in the restructure algorithm, so you ought to
    // get the position of x by doing the children follow as per the following:
    // let z be the first unbalanced node encountered going up from w toward the root
    // of T. Also, let y be the child of z with larger height (note that node y is
    // the child of z that is not an ancestor of w), and let x be the child of y
    // defined as follows: if one of the children of y is taller than the other, let x
    // be the taller child of y; else (both children of y have the same height), let x
    // be the child of y on the same side as y (that is, if y is a left child, let x
    // be the left child of y, else let x be the right child of y). In any case, we
    // then perform a restructure(x) operation, which restores the height-balance
    // property locally, at the subtree that was formerly rooted at z and is rooted
    // at the node we temporarily called b.

    // NOTE: Unfortunately, this trinode restructuring may reduce the height of subtree
    // rooted at b by 1, which may cause an ancestor of b to become unbalanced. So,
    // after rebalancing z, we continue walking up T looking for unbalanced nodes.
    // SO - we probably do need a checkIfSubtreeBalanced(x) function as well.

    // Node itself is a protected type of LinkedBinaryTree, so it can't be
    // named here -- but Position::get() still hands back a valid pointer to
    // one, and `auto` lets us hold onto it (and dereference it: Node's own
    // fields are public) without ever having to spell the type out.
    auto* x = v.get();
    auto* y = x->parent;
    auto* z = y->parent;
    auto* z_parent = z->parent;

    // Which slot of z_parent currently holds z. This is *independent* of
    // which side y hangs off z (z can be z_parent's left child while y is
    // z's right child -- an "inner" grandchild -- just as easily as the
    // "outer" case where both sides match). Whichever node ends up
    // promoted to z's old spot (y for a single rotation, x for a double
    // rotation) gets attached on *this* side of z_parent -- the shape
    // logic below must not also gate on it.
    bool zWasLeftChild = (z_parent->left == z);
    auto attachToZParent = [&](auto* promoted) {
        if (zWasLeftChild) {
            z_parent->left = promoted;
        } else {
            z_parent->right = promoted;
        }
        promoted->parent = z_parent;
    };

    // page 443 -- trinode restructuring, expressed as the 4 shapes {x,y,z}
    // can be in, based purely on (is y z's left or right child) x (is x
    // y's left or right child). Exactly one of these matches whenever
    // restructure is called correctly (x a child of y, y a child of z).
    if (z->right == y && y->right == x) {
        // case (a): right-right -> single left rotation, y takes z's spot
        attachToZParent(y);
        z->parent = y;
        z->right = y->left;
        z->right->parent = z;
        y->left = z;
    } else if (z->left == y && y->left == x) {
        // case (b): left-left -> single right rotation, y takes z's spot
        attachToZParent(y);
        z->parent = y;
        z->left = y->right;
        z->left->parent = z;
        y->right = z;
    } else if (z->right == y && y->left == x) {
        // case (c): right-left -> double rotation, x takes z's spot
        attachToZParent(x);
        z->right = x->left;
        z->right->parent = z;
        y->left = x->right;
        y->left->parent = y;
        x->left = z;
        z->parent = x;
        x->right = y;
        y->parent = x;
    } else if (z->left == y && y->right == x) {
        // case (d): left-right -> double rotation, x takes z's spot
        attachToZParent(x);
        z->left = x->right;
        z->left->parent = z;
        y->right = x->left;
        y->right->parent = y;
        x->right = z;
        z->parent = x;
        x->left = y;
        y->parent = x;
    } else {
        // x/y/z didn't form a valid trinode (x not a child of y, or y not
        // a child of z) -- a precondition violation by the caller, not
        // something that should happen in normal AVL use.
        throw std::logic_error(
            "restructure: v, parent(v), grandparent(v) are not a valid trinode");
    }

    return TPos(zWasLeftChild ? z_parent->left : z_parent->right);
}