#include "../common/Singly_Linked_List.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class MyHashMap {
public:
    int space;
    using kvp = pair<int, int>;
    vector<SLinkedList<kvp>> bucketlist;
    struct KeyOnlyEqual {
        bool operator()(const kvp& stored, const kvp& target)
        {
            return stored.first == target.first;
        }
    };

    MyHashMap()
        : space(1000)
        , bucketlist(space, SLinkedList<pair<int, int>>())
    {
    }

    size_t knuthHash(int key, size_t space)
    {
        uint32_t A = 2654435769u; // 2^32 * (golden ratio - 1)
        uint32_t hash = static_cast<uint32_t>(key) * A; // implicit mod 2^32 via overflow
        return hash % space;
    }

    void put(int key, int value)
    {
        size_t idx = knuthHash(key, space); // space = 1000, idx in [0, 1000)
        if (bucketlist[idx].contains(kvp(key, 0), KeyOnlyEqual {})) {
            SNode<kvp>* delNode = bucketlist[idx].find(kvp(key, 0), KeyOnlyEqual {});
            bucketlist[idx].remove(delNode);
        }
        bucketlist[idx].addFront(kvp(key, value));
    }

    int get(int key)
    {
        size_t idx = knuthHash(key, space);
        // auto containsKey = [](const kvp& stored, const kvp& target) -> bool {
        //     return stored.first == target.first;
        // };
        if (!bucketlist[idx].contains(kvp(key, 0), KeyOnlyEqual {})) {
            return -1;
        }
        SNode<kvp>* res = bucketlist[idx].find(kvp(key, 0), KeyOnlyEqual {});
        return res->elem.second;
    }

    void remove(int key)
    {
        size_t idx = knuthHash(key, space);
        // auto containsKey = [](const kvp& stored, const kvp& target) -> bool {
        //     return stored.first == target.first;
        // };
        if (!bucketlist[idx].contains(kvp(key, 0), KeyOnlyEqual {})) {
            return;
        }
        SNode<kvp>* delNode = bucketlist[idx].find(kvp(key, 0), KeyOnlyEqual {});
        bucketlist[idx].remove(delNode);
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

int main()
{
    MyHashMap* obj = new MyHashMap();
    vector<string> operations = { "put", "put", "get", "get", "put", "get", "remove", "get" };
    vector<vector<int>> values = { { 1, 1 }, { 2, 2 }, { 1 }, { 3 }, { 2, 1 }, { 2 }, { 2 }, { 2 } };
    for (size_t i = 0; i < operations.size(); ++i) {
        if (i == 8) {
            std::cout << std::endl;
        }
        if (operations[i] == "put") {
            obj->put(values[i][0], values[i][1]);
            continue;
        }
        if (operations[i] == "get") {
            std::cout << obj->get(values[i][0]) << std::endl;
            continue;
        }
        if (operations[i] == "remove") {
            obj->remove(values[i][0]);
            continue;
        }
    }
    delete obj;
    return 0;
}