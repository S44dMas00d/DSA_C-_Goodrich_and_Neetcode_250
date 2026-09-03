#include "../common/Linked_Binary_Tree.hpp"
#include <iostream>

using namespace std;

int main()
{
    LinkedBinaryTree<int> t;
    cout << t.empty() << endl;
    cout << t.size() << endl;
    cout << t.positions().size() << endl; // empty tree -> should be 0, not crash

    t.addRoot();
    *t.root() = 1;
    cout << t.empty() << endl;
    cout << t.size() << endl;

    LinkedBinaryTree<int>::Position p = t.root();
    t.expandExternal(p);
    *(p.left()) = 2;
    *(p.right()) = 3;
    cout << t.size() << endl; // expect 3 (root + 2 children)

    for (auto& pos : t.positions()) // preorder: 1 2 3
        cout << *pos << " ";
    cout << endl;

    cout << p.isRoot() << endl; // 1
    cout << p.isExternal() << endl; // 0 - root now has children
    cout << p.left().isExternal() << endl; // 1 - leaf

    // removes leaf '2' along with its parent (the root, '1'),
    // promoting sibling '3' to take the root's place
    LinkedBinaryTree<int>::Position newRoot = t.removeAboveExternal(p.left());
    cout << t.size() << endl; // expect 1
    cout << *newRoot << endl; // 3
    cout << newRoot.isRoot() << endl; // 1

    for (auto& pos : t.positions())
        cout << *pos << " ";
    cout << endl;

    return 0;
}
