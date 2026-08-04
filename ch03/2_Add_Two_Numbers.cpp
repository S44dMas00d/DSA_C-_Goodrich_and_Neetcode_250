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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        if (!l1 & !l2) {
            return nullptr;
        } else if (!l1) {
            return l2;
        } else if (!l2) {
            return l1;
        }
        ListNode* head = nullptr;
        ListNode* head1 = l1;
        ListNode* head2 = l2;
        ListNode* curr = nullptr;
        ListNode* prev = nullptr;
        int carry = 0;
        int remainder = 0;
        while (head1 || head2 || carry) {
            int sum = (head1 ? head1->elem : 0) + (head2 ? head2->elem : 0) + carry;
            carry = static_cast<int>((sum) / 10);
            remainder = sum % 10;
            curr = new ListNode();
            curr->elem = remainder;
            if (!prev) {
                head = curr;
            } else {
                prev->next = curr;
            }
            prev = curr;
            head1 = head1 ? head1->next : nullptr;
            head2 = head2 ? head2->next : nullptr;
        }
        return head;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL1;
    SLinkedList<int> SLL2;
    std::vector<int> nums1 = { 3, 4, 2 };
    std::vector<int> nums2 = { 4, 6, 5 };
    for (size_t i = 0; i < nums1.size(); i++) {
        SLL1.addFront(nums1[i]);
    }
    for (size_t i = 0; i < nums2.size(); i++) {
        SLL2.addFront(nums2[i]);
    }
    ListNode* refNode1 = SLL1.head;
    ListNode* refNode2 = SLL2.head;
    std::cout << "SLL1: " << std::endl;
    while (refNode1) {
        std::cout << refNode1->elem << std::endl;
        refNode1 = refNode1->next;
    }
    std::cout << "SLL2: " << std::endl;
    while (refNode2) {
        std::cout << refNode2->elem << std::endl;
        refNode2 = refNode2->next;
    }
    std::cout << "New List: " << std::endl;
    // Sol.reorderList(SLL.head);
    ListNode* refNodeRes = Sol.addTwoNumbers(SLL1.head, SLL2.head);
    while (refNodeRes) {
        std::cout << refNodeRes->elem << std::endl;
        refNodeRes = refNodeRes->next;
    }
    std::cout << std::endl;
    return 0;
}
