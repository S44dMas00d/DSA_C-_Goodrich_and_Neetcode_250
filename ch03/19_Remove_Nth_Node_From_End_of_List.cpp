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
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        // deal with edgecases:
        // if no head
        if (!head) {
            return nullptr;
        }

        // one node and n=1
        if (head && !head->next && n == 1) {
            return nullptr;
        }
        ListNode dummy;
        dummy.next = head;
        ListNode* foreNode = &dummy;
        ListNode* aftNode = &dummy;
        foreNode->next = head;
        aftNode->next = head;
        int stepCount = 0;
        while (foreNode->next) {
            if (stepCount >= n) {
                aftNode = aftNode->next;
            }
            foreNode = foreNode->next;
            stepCount++;
        }
        if (aftNode->next == head) {
            head = aftNode->next->next;
        } else {
            aftNode->next = aftNode->next->next;
        }
        return head;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL;
    // std::vector<int> nums = { 5, 4, 3, 2, 1 };
    std::vector<int> nums = { 2, 1 };
    // std::vector<int> nums = { 1 };
    for (size_t i = 0; i < nums.size(); i++) {
        SLL.addFront(nums[i]);
    }
    ListNode* refNode = SLL.head;
    while (refNode) {
        std::cout << refNode->elem << std::endl;
        refNode = refNode->next;
    }
    std::cout << std::endl;
    ListNode* resNode = Sol.removeNthFromEnd(SLL.head, 2);
    while (resNode) {
        std::cout << resNode->elem << std::endl;
        resNode = resNode->next;
    }
    std::cout << std::endl;
    return 0;
}
