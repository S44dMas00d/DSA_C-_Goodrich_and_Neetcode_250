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
    int pairSum(ListNode* head)
    {
        // step 0 is to deal with the empty list edge case and the single
        // entry edge case since we need at least one pair for the twin
        if (!head || !head->next) {
            return 0;
        }
        // ok so step 1 is to find the midpoint of the linked list
        // as well as figure out the count / size of the list as well as
        // figure out the midpoint which out to fall at n/2 for n total count
        ListNode dummy;
        ListNode* dummyPtr = &dummy;
        dummyPtr->next = head;
        ListNode* head1 = head;
        ListNode* fast = head;
        ListNode* slow = head;
        int countNodes = 1;
        while (fast) {
            fast = fast->next->next;
            slow = slow->next;
            dummyPtr = dummyPtr->next;
            countNodes += 2;
        }
        // right now dummy is the node behind slow and so we need to use to to sever
        // the connection between the first and second halves;
        dummyPtr->next = nullptr;
        // we arrive at step 2 - where we have the midpoint and we need to reverse
        // now that slow pointer points to n/2 or the actual midpoint for
        // an even element list we ought to reverse the second half of the
        // linked list
        ListNode* head2 = slow;
        // head2->next = nullptr;
        ListNode* nextNode = slow->next;
        while (nextNode) {
            ListNode* old = head2;
            head2 = nextNode;
            nextNode = head2->next;
            head2->next = old;
            old = head2;
        }
        slow->next = nullptr;
        // we arrive at step 3 and here we need to essentially maintain a maxSum variable
        // and we need to run with the heads of both the lists, i.e., head1 and slow. we
        // aren't sure if their tails are properly configured since we set none around the
        // half point to a nullptr, so we use the countNodes/2 to stop short of the half point
        int maxSum = 0;
        int stepsTaken = 0;
        while (stepsTaken < (countNodes / 2)) {
            int sum = head1->elem + head2->elem;
            maxSum = (sum > maxSum) ? sum : maxSum;
            stepsTaken++;
            head2 = head2->next;
            head1 = head1->next;
        }
        return maxSum;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL;
    std::vector<int> nums = { 1, 2, 4, 5 };
    for (size_t i = 0; i < nums.size(); i++) {
        SLL.addFront(nums[i]);
    }
    ListNode* refNode = SLL.head;
    while (refNode) {
        std::cout << refNode->elem << std::endl;
        refNode = refNode->next;
    }
    std::cout << std::endl;
    int pairSumRes = Sol.pairSum(SLL.head);
    std::cout << pairSumRes << std::endl;
    return 0;
}
