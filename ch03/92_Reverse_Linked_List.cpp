#include "../common/Singly_Linked_List.hpp"
#include <iostream>
#include <vector>

using ListNode = SNode<int>;
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
    ListNode* reverseBetween(ListNode* head, int left, int right)
    {
        if (!head || (right - left < 1)) {
            return head;
        }
        ListNode dummy = ListNode();
        dummy.elem = -1;
        dummy.next = head;
        int index_left = 1;
        int index_right = 1;
        ListNode* prev_left = &dummy;
        ListNode* prev_right = &dummy;
        ListNode* curr_left = head;
        ListNode* curr_right = head;
        ListNode* next_left = head->next;
        ListNode* next_right = head->next;
        int gap = right - left;
        while (index_right <= (right + 1) && curr_right->next) {
            if ((index_right - index_left) == (gap + 1)) {
                prev_left = prev_left->next;
                curr_left = curr_left->next;
                next_left = next_left->next;
                index_left++;
            }
            prev_right = prev_right->next;
            curr_right = curr_right->next;
            next_right = next_right->next;
            index_right++;
        }
        // perform the swap
        curr_left->next = nullptr;
        curr_right->next = nullptr;

        prev_left->next = curr_right;
        curr_right->next = next_left;

        prev_right->next = curr_left;
        curr_left->next = next_right;
        return head;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL1;
    std::vector<int> nums1 = { 5, 4, 3, 2, 1 };
    // std::vector<int> nums1 = { 5, 3 };
    for (size_t i = 0; i < nums1.size(); i++) {
        SLL1.addFront(nums1[i]);
    }
    ListNode* refNode1 = SLL1.head;
    std::cout << "SLL1: " << std::endl;
    while (refNode1) {
        std::cout << refNode1->elem << std::endl;
        refNode1 = refNode1->next;
    }
    std::cout << "New List: " << std::endl;
    // Sol.reorderList(SLL.head);
    ListNode* refNodeRes = Sol.reverseBetween(SLL1.head, 2, 4);
    while (refNodeRes) {
        std::cout << refNodeRes->elem << std::endl;
        refNodeRes = refNodeRes->next;
    }
    std::cout << std::endl;
    return 0;
}
