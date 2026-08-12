#include "../common/Doubly_Linked_List.hpp"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

struct LRUCacheNodeData {
    int key;
    int value;
};

class LRUCache {
public:
    std::unordered_map<int, DNode<LRUCacheNodeData>*> MapKeyNode;
    DLinkedList<LRUCacheNodeData> DLL;
    int size;
    int capacity;

public:
    LRUCache(int capacity)
        : MapKeyNode()
        , DLL()
        , size(0)
        , capacity(capacity)
    {
    }
    int get(int key)
    {
        if (!MapKeyNode.count(key)) {
            return -1;
        }

        DNode<LRUCacheNodeData>* node = MapKeyNode.at(key);

        // Already most recently used
        if (node->prev != DLL.header) {
            // Remove node from its current position
            node->prev->next = node->next;
            node->next->prev = node->prev;

            // Insert node at the front (MRU)
            node->next = DLL.header->next;
            node->prev = DLL.header;
            DLL.header->next->prev = node;
            DLL.header->next = node;
        }

        return node->elem.value;
    }

    void put(int key, int value)
    {
        // Key already exists
        if (MapKeyNode.count(key)) {
            DNode<LRUCacheNodeData>* node = MapKeyNode.at(key);

            // Update value
            node->elem.value = value;

            // Move to front (MRU)
            if (node->prev != DLL.header) {
                // Remove from current position
                node->prev->next = node->next;
                node->next->prev = node->prev;

                // Insert at front
                node->next = DLL.header->next;
                node->prev = DLL.header;
                DLL.header->next->prev = node;
                DLL.header->next = node;
            }

            return;
        }

        // Key does not exist
        if (size >= capacity) {
            LRUCacheNodeData dataToRemove = DLL.back();
            MapKeyNode.erase(dataToRemove.key);
            DLL.removeBack();
            size--;
        }

        LRUCacheNodeData data;
        data.key = key;
        data.value = value;

        DNode<LRUCacheNodeData>* addedNodeRef = DLL.addFrontwRefReturn(data);

        MapKeyNode.insert({ key, addedNodeRef });
        size++;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{
    LRUCache LRU(2);
    // std::vector<std::pair<int, int>> pair_vec = { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 } };
    // for (size_t i = 0; i < pair_vec.size(); i++) {
    //     LRU.put(pair_vec[i].first, pair_vec[i].second);
    // }
    // DNode<LRUCacheNodeData>* refDNode = LRU.DLL.header->next;
    // while (refDNode != LRU.DLL.trailer) {
    //     std::cout << "Key: " << refDNode->elem.key << " | Value: " << refDNode->elem.value << std::endl;
    //     refDNode = refDNode->next;
    // }

    LRU.put(1, 1);
    LRU.put(2, 2);
    std::cout << LRU.get(1) << std::endl;
    LRU.put(3, 3);
    std::cout << LRU.get(2) << std::endl;
    LRU.put(4, 4);
    std::cout << LRU.get(1) << std::endl;
    std::cout << LRU.get(3) << std::endl;
    std::cout << LRU.get(4) << std::endl;

    return 0;
}