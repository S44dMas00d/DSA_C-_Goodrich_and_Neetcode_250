#pragma once
#include <functional>
#include <list>
#include <stdexcept>

template <typename E>
class LinkedBinaryTree {
protected:
    struct Node {
        E e;
        Node* parent;
        Node* left;
        Node* right;
        Node()
            : e()
            , parent(nullptr)
            , left(nullptr)
            , right(nullptr)
        {
        }
    };

public:
    class Position {
    private:
        Node* v;

    public:
        Position(Node* _v = nullptr)
            : v(_v)
        {
        }
        E& operator*() const
        {
            return v->e;
        }
        E* operator->() const
        {
            return &v->e;
        }
        Position left() const
        {
            return Position(v->left);
        }
        Position right() const
        {
            return Position(v->right);
        }
        Position parent() const
        {
            return Position(v->parent);
        }
        bool isRoot() const
        {
            return v->parent == nullptr;
        }
        bool isExternal() const
        {
            return v->left == nullptr && v->right == nullptr;
        }
        bool isInternal() const
        {
            return !isExternal();
        }
        bool operator==(const Position& p) const
        {
            return v == p.v;
        }
        bool operator!=(const Position& p) const
        {
            return v != p.v;
        }
        friend class LinkedBinaryTree;
    };

public:
    LinkedBinaryTree();
    ~LinkedBinaryTree();
    int size() const;
    bool empty() const;
    Position root() const;
    void addRoot();
    void expandExternal(const Position& p);
    Position removeAboveExternal(const Position& p);
    std::list<Position> positions() const;

protected:
    void preorder(Node* v, std::function<void(Node*)>) const;

private:
    void destroySubtree(Node* v); // postorder-deletes v and everything below it
    Node* _root;
    int n;
};

template <typename E>
LinkedBinaryTree<E>::LinkedBinaryTree()
    : _root(nullptr)
    , n(0)
{
}

template <typename E>
void LinkedBinaryTree<E>::destroySubtree(Node* v)
{
    if (v == nullptr)
        return;
    destroySubtree(v->left);
    destroySubtree(v->right);
    delete v;
}

template <typename E>
LinkedBinaryTree<E>::~LinkedBinaryTree()
{
    destroySubtree(_root);
}

template <typename E>
int LinkedBinaryTree<E>::size() const
{
    return n;
}

template <typename E>
bool LinkedBinaryTree<E>::empty() const
{
    return n == 0;
}

template <typename E>
LinkedBinaryTree<E>::Position LinkedBinaryTree<E>::root() const
{
    return Position(_root);
}

template <typename E>
void LinkedBinaryTree<E>::addRoot()
{
    _root = new Node;
    n = 1;
}

template <typename E>
void LinkedBinaryTree<E>::expandExternal(const Position& p)
{
    Node* v = p.v;
    v->left = new Node;
    v->left->parent = v;
    v->right = new Node;
    v->right->parent = v;
    n += 2;
}

template <typename E>
LinkedBinaryTree<E>::Position
LinkedBinaryTree<E>::removeAboveExternal(const Position& p)
{
    Node* w = p.v;
    Node* v = w->parent;
    Node* sib = (w == v->left ? v->right : v->left);
    if (v == _root) {
        _root = sib;
        sib->parent = nullptr;
    } else {
        Node* gpar = v->parent;
        if (v == gpar->left) {
            gpar->left = sib;
        } else {
            gpar->right = sib;
        }
        sib->parent = gpar;
    }
    delete w;
    delete v;
    n -= 2;
    return Position(sib);
}

template <typename E>
void LinkedBinaryTree<E>::preorder(
    Node* v,
    std::function<void(Node*)> func) const
{
    if (v == nullptr)
        return;
    func(v);
    if (v->left) {
        preorder(v->left, func);
    }
    if (v->right) {
        preorder(v->right, func);
    }
}

template <typename E>
std::list<typename LinkedBinaryTree<E>::Position>
LinkedBinaryTree<E>::positions() const
{
    std::list<Position> posList;
    preorder(_root, [&posList](Node* currNode) {
        posList.push_back(Position(currNode));
    });
    return posList;
}