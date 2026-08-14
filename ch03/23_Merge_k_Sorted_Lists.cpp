#include "../common/Singly_Linked_List.hpp"
#include <iostream>
#include <limits>
#include <vector>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

using ListNode = SNode<int>;
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        // we first make the cursor array which will allow us to look at the
        // the LLs in lists as column accessible using these cursors.
        vector<ListNode*> listCursors(lists.size(), nullptr);
        int minValue = std::numeric_limits<int>::max();
        for (size_t i = 0; i < lists.size(); ++i) {
            listCursors[i] = lists[i];
            if (lists[i] && lists[i]->elem < minValue) {
                minValue = lists[i]->elem;
            }
        }
        // we now instantiate the header and dummy nodes for our new list to which
        // we will all the nodes from the other lists
        ListNode* headerNewList = new ListNode();
        // headerNewList->elem = -100;
        headerNewList->elem = minValue;
        headerNewList->next = nullptr;
        ListNode* cursor = headerNewList;

        // now we need to make the external loop such that it keeps running until all cursors
        // are removed from it:
        int gap = 0;
        while (listCursors.size() > 0) {
            size_t i = 0;
            while (i < listCursors.size()) {

                if (listCursors[i] == nullptr) {
                    listCursors.erase(listCursors.begin() + i);
                    continue;
                }

                if (gap == abs(cursor->elem - listCursors[i]->elem)) {
                    cursor->next = listCursors[i];
                    listCursors[i] = listCursors[i]->next;
                    cursor = cursor->next;
                    cursor->next = nullptr;
                    gap = 0;
                    continue;
                }
                i++;
            }
            gap++;
        }
        ListNode* oldcursor = headerNewList;
        headerNewList = headerNewList->next ? headerNewList->next : nullptr;
        delete oldcursor;
        return headerNewList;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL1;
    SLinkedList<int> SLL2;
    SLinkedList<int> SLL3;
    std::vector<int> nums1 = {};
    std::vector<int> nums2 = { -2 };
    std::vector<int> nums3 = { 1, -2, -3 };
    for (size_t i = 0; i < nums1.size(); i++)
        SLL1.addFront(nums1[i]);
    for (size_t i = 0; i < nums2.size(); i++)
        SLL2.addFront(nums2[i]);
    for (size_t i = 0; i < nums3.size(); i++)
        SLL3.addFront(nums3[i]);
    ListNode* headL1 = SLL1.head;
    ListNode* headL2 = SLL2.head;
    ListNode* headL3 = SLL3.head;
    while (headL1) {
        std::cout << headL1->elem << std::endl;
        headL1 = headL1->next;
    }
    std::cout << std::endl;
    while (headL2) {
        std::cout << headL2->elem << std::endl;
        headL2 = headL2->next;
    }
    std::cout << std::endl;
    while (headL3) {
        std::cout << headL3->elem << std::endl;
        headL3 = headL3->next;
    }
    std::cout << std::endl;
    headL1 = SLL1.head;
    headL2 = SLL2.head;
    headL3 = SLL3.head;
    vector<ListNode*> kLists = { headL1, headL2, headL3 };
    ListNode* headLMerged = Sol.mergeKLists(kLists);
    // doing this is necessary since their nodes are no longer
    // representative of their original structures or positions,
    // we set them to null so as to give nothing to their destructors
    // to chew on.
    SLL1.head = nullptr;
    SLL2.head = nullptr;
    SLL3.head = nullptr;
    SLinkedList<int> SLLMerged;
    SLLMerged.head = headLMerged;
    while (headLMerged) {
        std::cout << headLMerged->elem << std::endl;
        headLMerged = headLMerged->next;
    }
    std::cout << std::endl;
    // `merged` goes out of scope at the end of main()
    // and frees the chain exactly once.
    return 0;
}