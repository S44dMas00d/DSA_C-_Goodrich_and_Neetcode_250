#include "../common/Singly_Linked_List.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

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
        return std::floor(10000 * fract_part);
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
    std::vector<std::string> operations = { "MyHashSet", "add", "add", "add", "add", "contains", "remove", "add", "add", "add", "add" };
    std::vector<int> operations = { 12, 15, 17, 5, 12, 9, 2, 8, 2, 10 };
}