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
    struct recursiveReturnData {
        ListNode* retNode;
        int carry;
    };

    recursiveReturnData recursiveHelper(ListNode* curr1, ListNode* curr2)
    {
        if (!curr1 && !curr2) {
            return recursiveReturnData { nullptr, 0 };
        }
        ListNode* temp1 = curr1;
        ListNode* temp2 = curr2;
        curr1 = curr1 ? curr1->next : nullptr;
        curr2 = curr2 ? curr2->next : nullptr;
        recursiveReturnData returnedItems = recursiveHelper(curr1, curr2);
        int sum = (temp1 ? temp1->elem : 0) + (temp2 ? temp2->elem : 0) + returnedItems.carry;
        int remainder = sum % 10;
        int carry = static_cast<int>(sum / 10);
        ListNode* newNode = new ListNode();
        newNode->elem = remainder;
        newNode->next = returnedItems.retNode;
        return recursiveReturnData { newNode, carry };
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode* head1 = l1;
        ListNode* head2 = l2;
        ListNode* curr1 = l1;
        ListNode* curr2 = l2;
        // for the recursive approach to work as written above
        // we need to ensure that they are of the same lengths
        // so we need to add nodes {0, ->} in them to match sizes
        int numNodesShort = 0;
        bool isL1short = false;
        bool isL2short = false;
        while (curr1 || curr2) {
            if (!curr1 && curr2) {
                isL1short = true;
                numNodesShort++;
            } else if (curr1 && !curr2) {
                isL2short = true;
                numNodesShort++;
            }
            curr1 = curr1 ? curr1->next : nullptr;
            curr2 = curr2 ? curr2->next : nullptr;
        }

        while (numNodesShort) {
            ListNode* newNode = new ListNode();
            newNode->elem = 0;
            if (isL1short) {
                newNode->next = head1;
                head1 = newNode;
            } else if (isL2short) {
                newNode->next = head2;
                head2 = newNode;
            }
            numNodesShort--;
        }

        recursiveReturnData res = recursiveHelper(head1, head2);
        if (res.carry) {
            ListNode* head = new ListNode();
            head->elem = res.carry;
            head->next = res.retNode;
            return head;
        }
        return res.retNode;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL1;
    SLinkedList<int> SLL2;
    std::vector<int> nums1 = { 3, 4, 2, 7 };
    std::vector<int> nums2 = { 4, 6, 5 };
    // std::vector<int> nums1 = { 3, 2, 1 };
    // std::vector<int> nums2 = { 3, 2, 1 };
    // std::vector<int> nums1 = { 8, 7, 6 };
    // std::vector<int> nums2 = { 6, 7, 8 };
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
