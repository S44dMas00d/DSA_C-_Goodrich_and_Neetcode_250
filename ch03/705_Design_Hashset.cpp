#include "../common/Singly_Linked_List.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

// Link to Question:
// https://leetcode.com/problems/design-hashset/

class MyHashSet {
public:
    std::vector<SLinkedList<int>> arr;

    MyHashSet()
        : arr(1000, SLinkedList<int>())
    {
    }

    int knuth_multiplicative_hash(int key)
    {
        double A = (std::sqrt(5) - 1) / 2;
        // Use std::fmod instead of %
        double fract_part = std::fmod(key * A, 1.0);
        return std::floor(1000 * fract_part);
    }

    void add(int key)
    {
        int hash = knuth_multiplicative_hash(key);
        if (arr.size() <= hash) {
            arr.resize(hash * 2);
        }
        // first check if it exists and add if it doesnt:

        if (!arr[hash].contains(key))
            arr[hash].addFront(key);
    }

    void remove(int key)
    {
        int hash = knuth_multiplicative_hash(key);
        SNode<int>* keyPtr = arr[hash].find(key);
        if (keyPtr == nullptr)
            return;
        arr[hash].remove(keyPtr);
    }

    bool contains(int key)
    {
        int hash = knuth_multiplicative_hash(key);
        return arr[hash].contains(key);
    }
};
/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

int main()
{
    MyHashSet* obj = new MyHashSet();
    // obj->add(1);
    // std::cout << obj->contains(1) << std::endl;
    // std::cout << obj->contains(3) << std::endl;
    // obj->add(2); // set = [1, 2]
    // std::cout << obj->contains(2) << std::endl;
    // obj->remove(2); // set = [1]
    // std::cout << obj->contains(2) << std::endl;
    std::vector<std::string> operations = { "add", "add", "add", "add", "contains", "remove", "add", "add", "add", "add" };
    std::vector<int> values = { 12, 15, 17, 5, 12, 9, 2, 8, 2, 10 };
    for (size_t i = 0; i < operations.size(); ++i) {
        if (i == 8) {
            std::cout << std::endl;
        }
        if (operations[i] == "add") {
            obj->add(values[i]);
            continue;
        }
        if (operations[i] == "contains") {
            std::cout << obj->contains(values[i]) << std::endl;
            continue;
        }
        if (operations[i] == "remove") {
            obj->remove(values[i]);
            continue;
        }
    }
}