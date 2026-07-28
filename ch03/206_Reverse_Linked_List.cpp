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
    ListNode* reverseList(ListNode* head)
    {
        ListNode* head2 = nullptr;
        while (head != nullptr) {
            ListNode* old = head;
            head = head->next;
            if (head2) {
                old->next = head2;
            } else {
                old->next = nullptr;
            }
            head2 = old;
        }
        return head2;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL;
    // std::vector<int> nums = { 1, 2, 3, 4, 5 };
    std::vector<int> nums = { 5, 4, 3, 2, 1 };
    for (size_t i = 0; i < nums.size(); i++) {
        SLL.addFront(nums[i]);
    }
    ListNode* refNode = SLL.head;
    while (refNode) {
        std::cout << refNode->elem << std::endl;
        refNode = refNode->next;
    }
    std::cout << std::endl;
    // now with the linked list constructed and printed
    // we need a way to reverse it - then reprint it to test.
    refNode = Sol.reverseList(SLL.head);
    while (refNode) {
        std::cout << refNode->elem << std::endl;
        refNode = refNode->next;
    }

    return 0;
}