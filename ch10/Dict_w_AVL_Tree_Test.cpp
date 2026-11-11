#include "../common/Dict_w_AVL_Tree.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    AVLTreeDict<Entry<int, string>> D;

    // Sorted-order insertion (1, 2, 3, ...) is the case that would make a
    // plain, unbalanced BST degenerate into a straight line -- this is the
    // exact input restructure()'s "case (a)" single left rotation exists
    // to fix. Insert enough of it to also force double rotations later on.
    for (int k = 1; k <= 15; ++k) {
        D.insert(k, "v" + to_string(k));
    }
    cout << D.size() << endl; // 15

    // A balanced AVL tree over 15 keys has height 4 (a plain BST fed this
    // same sorted input would have height 15 -- one long right-leaning
    // chain). Traversal must still come out sorted either way.
    for (auto it = D.begin(); it != D.end(); ++it) {
        cout << (*it).key() << " ";
    }
    cout << endl; // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

    auto found = D.find(9);
    cout << (found != D.end()) << endl; // 1
    cout << (*found).value() << endl; // v9
    cout << (D.find(999) == D.end()) << endl; // 1 - not present

    // Erase enough keys, in an order chosen to trigger rebalancing on the
    // delete path too (not just insert), and confirm the dictionary is
    // still sorted and consistent afterward.
    int toErase[] = { 1, 2, 3, 15, 14, 13, 8 };
    for (int k : toErase) {
        D.erase(k);
    }
    cout << D.size() << endl; // 8
    for (auto it = D.begin(); it != D.end(); ++it) {
        cout << (*it).key() << " ";
    }
    cout << endl; // 4 5 6 7 9 10 11 12

    auto it9 = D.find(9);
    D.erase(it9); // erase via iterator
    cout << D.size() << endl; // 7

    try {
        D.erase(12345); // not present -> throws
    } catch (const NonexistentElement& e) {
        cout << "caught: " << e.what() << endl;
    }

    while (!D.empty()) {
        D.erase(D.begin());
    }
    cout << D.empty() << endl; // 1
    cout << (D.begin() == D.end()) << endl; // 1
}
