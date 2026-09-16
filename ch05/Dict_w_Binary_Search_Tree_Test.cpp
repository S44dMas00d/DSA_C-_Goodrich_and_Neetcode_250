#include "../common/Dict_w_Binary_Search_Tree.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    SearchTreeDict<Entry<int, string>> D;
    cout << D.empty() << endl; // 1
    cout << D.size() << endl; // 0
    cout << (D.begin() == D.end()) << endl; // 1 - empty range

    // BST shape ends up:
    //              50
    //            /       \.
    //          30         70
    //         /   \      /   \.
    //       20     40  60     80
    //       /
    //      10
    int keys[] = { 50, 30, 70, 20, 40, 60, 80, 10 };
    for (int k : keys) {
        D.insert(k, "v" + to_string(k));
    }
    cout << D.size() << endl; // 8

    for (auto it = D.begin(); it != D.end(); ++it) {
        cout << (*it).key() << " ";
    }
    cout << endl; // 10 20 30 40 50 60 70 80  (in-order traversal == sorted keys)

    auto found = D.find(40);
    cout << (found != D.end()) << endl; // 1
    cout << (*found).value() << endl; // v40
    cout << (D.find(999) == D.end()) << endl; // 1 - not present

    D.erase(10); // leaf erase
    D.erase(30); // erase a node with two children (20 and 40)
    for (auto it = D.begin(); it != D.end(); ++it) {
        cout << (*it).key() << " ";
    }
    cout << endl; // 20 40 50 60 70 80
    cout << D.size() << endl; // 6

    auto it70 = D.find(70);
    D.erase(it70); // erase via iterator
    for (auto it = D.begin(); it != D.end(); ++it) {
        cout << (*it).key() << " ";
    }
    cout << endl; // 20 40 50 60 80

    D.erase(50); // erase the root itself
    for (auto it = D.begin(); it != D.end(); ++it) {
        cout << (*it).key() << " ";
    }
    cout << endl; // 20 40 60 80

    try {
        D.erase(12345); // not present -> throws
    } catch (const NonexistentElement& e) {
        cout << "caught: " << e.what() << endl;
    }

    // Dictionary (not Map) semantics: duplicate keys are allowed.
    SearchTreeDict<Entry<int, string>> Dup;
    Dup.insert(5, "a");
    Dup.insert(5, "b");
    Dup.insert(5, "c");
    cout << Dup.size() << endl; // 3
    for (auto it = Dup.begin(); it != Dup.end(); ++it) {
        cout << (*it).key() << ":" << (*it).value() << " ";
    }
    cout << endl; // 5:a 5:b 5:c  (all three entries survive, in insertion-descent order)

    while (!D.empty()) {
        D.erase(D.begin());
    }
    cout << D.empty() << endl; // 1
    cout << (D.begin() == D.end()) << endl; // 1
}
