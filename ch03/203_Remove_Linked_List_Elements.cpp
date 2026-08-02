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
    ListNode* removeElements(ListNode* head, int val)
    {
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* curr = dummy;

        while (curr && curr->next) {
            if (curr->next->elem == val) {
                ListNode* old = curr->next;
                curr->next = curr->next->next;
                delete old;
            } else {
                curr = curr->next;
            }
        }
        // the real head might have changed so return dummy.next
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL;
    // std::vector<int> nums = { 1, 2, 2, 1 };
    // std::vector<int> nums = { 1, 0, 1 };
    // std::vector<int> nums = { 1, 2, 6, 3, 4, 5, 6 };
    // std::vector<int> nums = { 6, 5, 4, 3, 6, 2, 1, 6 };
    // std::vector<int> nums = { 6, 5, 4, 3, 6, 2, 1 };
    std::vector<int> nums = { 7, 7, 7, 7 };
    for (size_t i = 0; i < nums.size(); i++) {
        SLL.addFront(nums[i]);
    }
    ListNode* refNode = SLL.head;
    while (refNode) {
        std::cout << refNode->elem << std::endl;
        refNode = refNode->next;
    }
    std::cout << std::endl;
    ListNode* resNode = Sol.removeElements(SLL.head, 7);
    while (resNode) {
        std::cout << resNode->elem << std::endl;
        resNode = resNode->next;
    }
    delete SLL.head;
    std::cout << std::endl;
}
