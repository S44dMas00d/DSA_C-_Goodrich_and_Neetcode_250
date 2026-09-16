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