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
    bool isPalindrome(ListNode* head)
    {
        // first handle the case where both cant move one step
        // assume end is null pointer as per above definition
        if (head == nullptr || head->next == nullptr) {
            return true;
        }
        // if fast finished as nullptr we had even number of elements and if it wasnt null
        // then we had odd number of elements. this means that:
        // If fast == nullptr (Even length), slow is already at the start of the second half.
        // If fast != nullptr (Odd length), slow is the middle, so the second half starts at slow->next.
        ListNode* fast = head;
        ListNode* slow = head;
        int count = 0; // track how many steps slow takes
        // now we use fast to find the midpoint of the LL
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            count++;
        }
        // now the slow is representative of the LL midpoint.
        // redefined the two pointers for start and midpoint.
        ListNode* head2 = head;
        ListNode* start = nullptr;
        ListNode* mid = (fast == nullptr) ? slow : slow->next;

        // we need to reverse one of the two halves before
        // comparison is run, we choose the first half.
        // reverse exactly count elements for the first half:
        for (int i = 0; i < count; i++) {
            ListNode* old = head2;
            head2 = head2->next;
            old->next = start;
            start = old;
        }

        // while condition will remain the same.
        while (mid != nullptr) {
            if (start->elem != mid->elem) {
                return false;
            }
            start = start->next;
            mid = mid->next;
        }
        return true;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL;
    // std::vector<int> nums = { 1, 2, 2, 1 };
    std::vector<int> nums = { 1, 0, 1 };
    for (size_t i = 0; i < nums.size(); i++) {
        SLL.addFront(nums[i]);
    }
    ListNode* refNode = SLL.head;
    while (refNode) {
        std::cout << refNode->elem << std::endl;
        refNode = refNode->next;
    }
    std::cout << std::endl;
    bool isPalindromeRes = Sol.isPalindrome(SLL.head);
    std::cout << "is SLL palindrome? -> " << (isPalindromeRes ? "true" : "false") << std::endl;
}
