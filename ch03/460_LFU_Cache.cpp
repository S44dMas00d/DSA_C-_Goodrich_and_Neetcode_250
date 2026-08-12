#include "../common/Doubly_Linked_List.hpp"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

struct LFUNodeData {
    int key;
    int value;
    int count;
};

class LFUCache {
public:
    std::unordered_map<int, DNode<LFUNodeData>*> LFUNodeAddrMap;
    DNode<LFUNodeData>* dummyWallNode;
    DLinkedList<LFUNodeData> DLL;
    int size;
    int capacity;

    LFUCache(int capacity)
        : LFUNodeAddrMap()
        , DLL()
        , size(0)
        , capacity(capacity)
    {
        dummyWallNode = DLL.addwRefReturn(DLL.trailer, LFUNodeData { -1, -1, -1 });
    }

    void leftSwap(DNode<LFUNodeData>* dNodePtr)
    {

        // first check if the left node is head, if so return the value and return before left swap.
        if (dNodePtr->prev == DLL.header) {
            return;
        }

        // otherwise, we assume there is at least one other element between
        // this element and the head so we perform the leftwards swap
        // to swap we consider segment of four nodes that make up the one after DNodePtr, i.e., segmenttail
        // and the one two pointers before it, i.e., there is the prev which we need to swap with and then
        // there is the one before it which we call segment head.
        // SH = Segment Head
        // ST = Segment Tail
        DNode<LFUNodeData>* SH = dNodePtr->prev->prev;
        DNode<LFUNodeData>* ST = dNodePtr->next;
        DNode<LFUNodeData>* swap1 = dNodePtr->prev;
        DNode<LFUNodeData>* swap2 = dNodePtr;
        SH->next = swap2;
        swap2->prev = SH;
        ST->prev = swap1;
        swap1->next = ST;
        swap2->next = swap1;
        swap1->prev = swap2;
    }

    void leftSwapAcrossDummyWallNode(DNode<LFUNodeData>* dNodePtr)
    {
        DLL.removeWoDelete(dNodePtr);
        DLL.add(dummyWallNode, dNodePtr);
    }

    void promote(DNode<LFUNodeData>* dNodePtr)
    {
        if (dNodePtr->elem.count == 1) {
            leftSwapAcrossDummyWallNode(dNodePtr);
        }
        dNodePtr->elem.count++;
        while (dNodePtr->prev != DLL.header && dNodePtr->prev->elem.count <= dNodePtr->elem.count) {
            leftSwap(dNodePtr);
        }
    }

    int get(int key)
    {
        if (!LFUNodeAddrMap.count(key)) {
            return -1;
        }
        DNode<LFUNodeData>* dNodePtr = LFUNodeAddrMap.at(key);
        promote(dNodePtr);
        return dNodePtr->elem.value;
    }

    void put(int key, int value)
    {
        // Key already exists
        if (LFUNodeAddrMap.count(key)) {
            DNode<LFUNodeData>* dNodePtr = LFUNodeAddrMap.at(key);

            // Update value
            dNodePtr->elem.value = value;
            promote(dNodePtr);
            return;
        }
        // now if the key does not exist in the map - this means the key must be introduced into the map and DLL
        // however before we do this we need to make sure that the capacity condition is honored
        if (size >= capacity) {
            if (dummyWallNode->next == DLL.trailer) {
                LFUNodeAddrMap.erase(dummyWallNode->prev->elem.key);
                DLL.remove(dummyWallNode->prev);
            } else {
                LFUNodeAddrMap.erase(DLL.trailer->prev->elem.key);
                DLL.remove(DLL.trailer->prev);
            }
            size--;
        }

        // with the conditional removal done we can add the data to the front.
        DNode<LFUNodeData>* dNodePtr = DLL.addwRefReturn(dummyWallNode->next, LFUNodeData { key, value, 1 });
        LFUNodeAddrMap.insert({ key, dNodePtr });
        size++;
        return;
    };
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{
    // case 2 - fails when used only with addBack()
    LFUCache* LFU1 = new LFUCache(3);
    std::cout << "case 2: " << std::endl;
    LFU1->put(1, 1);
    LFU1->put(2, 2);
    LFU1->put(3, 3);
    LFU1->put(4, 4);
    std::cout << LFU1->get(4) << std::endl;
    std::cout << LFU1->get(3) << std::endl;
    std::cout << LFU1->get(2) << std::endl;
    std::cout << LFU1->get(1) << std::endl;
    LFU1->put(5, 5);
    std::cout << LFU1->get(1) << std::endl;
    std::cout << LFU1->get(2) << std::endl;
    std::cout << LFU1->get(3) << std::endl;
    std::cout << LFU1->get(4) << std::endl;
    std::cout << LFU1->get(5) << std::endl;
    std::cout << std::endl;

    // case 3 - fails when used only with addFront()
    LFUCache* LFU2 = new LFUCache(3);
    std::cout << "case 3: " << std::endl;
    LFU2->put(2, 2);
    LFU2->put(1, 1);
    std::cout << LFU2->get(2) << std::endl;
    std::cout << LFU2->get(1) << std::endl;
    std::cout << LFU2->get(2) << std::endl;
    LFU2->put(3, 3);
    LFU2->put(4, 4);
    std::cout << LFU2->get(3) << std::endl;
    std::cout << LFU2->get(2) << std::endl;
    std::cout << LFU2->get(1) << std::endl;
    std::cout << LFU2->get(4) << std::endl;
    std::cout << std::endl;

    // case 4 - fails when we used booth addFront and addBack
    LFUCache* LFU3 = new LFUCache(2);
    std::cout << "case 4: " << std::endl;
    LFU3->put(2, 1);
    LFU3->put(2, 2);
    std::cout << LFU3->get(2) << std::endl;
    LFU3->put(1, 1);
    LFU3->put(4, 1);
    std::cout << LFU3->get(2) << std::endl;

    return 0;
}
