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
    void reorderList(ListNode* head)
    {
        if (!head || !head->next) {
            return;
        }
        // we need to find the midpoint of the provided linked list
        ListNode dummy = ListNode();
        dummy.next = head;
        ListNode* head1 = head;
        ListNode* dummyPtr = &dummy;
        ListNode* fast = head;
        ListNode* slow = head;
        int nodeCount = 0;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next ? fast->next->next : nullptr;
            slow = slow->next;
            dummyPtr = dummyPtr->next;
            nodeCount++;
        }
        // now that we have the midpoint, we need to delete the link
        // between dummy and slow to sever the two halves
        dummyPtr->next = nullptr;
        // now with this done we need to begin reversing the second half and
        // also produce head2 for control of second half.
        ListNode* head2 = slow;
        ListNode* nextNode = slow->next;
        while (nextNode) {
            ListNode* old = head2;
            head2 = nextNode;
            nextNode = head2->next;
            head2->next = old;
            old = head2;
        }
        slow->next = nullptr;
        // now that we have the two separate lists we need to zip them up
        ListNode* curr1 = head1;
        ListNode* curr2 = head2;
        ListNode* old1 = curr1;
        ListNode* old2 = curr2;
        while (curr1) {
            curr1 = curr1->next;
            old1->next = curr2;
            curr2 = curr2->next;
            old2->next = curr1 ? curr1 : curr2;
            old1 = curr1;
            old2 = curr2;
        }
        return;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL;
    // std::vector<int> nums = { 5, 4, 3, 2, 1 };
    std::vector<int> nums = { 4, 3, 2, 1 };
    // std::vector<int> nums = { 2, 1 };
    // std::vector<int> nums = { 1 };
    for (size_t i = 0; i < nums.size(); i++) {
        SLL.addFront(nums[i]);
    }
    ListNode* refNode = SLL.head;
    std::cout << "Old List: " << std::endl;
    while (refNode) {
        std::cout << refNode->elem << std::endl;
        refNode = refNode->next;
    }
    std::cout << "New List: " << std::endl;
    Sol.reorderList(SLL.head);
    refNode = SLL.head;
    while (refNode) {
        std::cout << refNode->elem << std::endl;
        refNode = refNode->next;
    }
    std::cout << std::endl;
    return 0;
}
