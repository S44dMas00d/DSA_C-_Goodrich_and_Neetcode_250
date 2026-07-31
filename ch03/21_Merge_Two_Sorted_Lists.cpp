#include "../common/Singly_Linked_List.hpp"
#include <iostream>
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

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        ListNode* head_return = nullptr;
        ListNode* list_n = nullptr;
        // first check for the case where one of the lists is
        // empty - in which case we send back the pointer to
        // non empty lists head.
        if (!list1 && !list2) {
            return head_return;
        } else if (!list1) {
            return list2;
        } else if (!list2) {
            return list1;
        }

        // next we need to choose the element from the two heads
        // to serve as the head for list_n or the new list
        if (list1->elem <= list2->elem) {
            list_n = list1;
            head_return = list1;
            list1 = list1->next;
        } else {
            list_n = list2;
            head_return = list2;
            list2 = list2->next;
        }
        // with the proper head element now selected - we can
        // proceed with the proper steps for interlacing the lists
        while (list1 && list2) {
            if (list1->elem <= list2->elem) {
                list_n->next = list1;
                list1 = list1->next;
                list_n = list_n->next;
            } else if (list2->elem < list1->elem) {
                list_n->next = list2;
                list2 = list2->next;
                list_n = list_n->next;
            }
        }
        // at this point one of the lists, i.e., the shorter one has
        // exhausted all elements - we need to append the remaining
        // elements of the longer list to teh combined list
        if (!list1 && !list2) {
            return head_return;
        } else if (!list1) {
            list_n->next = list2;
        } else {
            list_n->next = list1;
        }
        return head_return;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL1;
    SLinkedList<int> SLL2;
    std::vector<int> nums1 = { 4, 2, 1 };
    std::vector<int> nums2 = { 4, 3, 1 };
    for (size_t i = 0; i < nums1.size(); i++)
        SLL1.addFront(nums1[i]);
    for (size_t i = 0; i < nums2.size(); i++)
        SLL2.addFront(nums2[i]);
    ListNode* headL1 = SLL1.head;
    ListNode* headL2 = SLL2.head;
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
    ListNode* headLMerged = Sol.mergeTwoLists(SLL1.head, SLL2.head);
    // doing this is necessary since their nodes are no longer
    // representative of their original structures or positions,
    // we set them to null so as to give nothing to their destructors
    // to chew on.
    SLL1.head = nullptr;
    SLL2.head = nullptr;
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