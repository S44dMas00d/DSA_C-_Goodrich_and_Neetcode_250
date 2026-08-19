#include "../common/Singly_Linked_List.hpp"
#include <iostream>
#include <limits>
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
using namespace std;

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
    int getGCD(int left, int right)
    {
        while (right != 0) {
            int temp = right;
            right = left % right;
            left = temp;
        }
        return left;
    }

    ListNode* insertGreatestCommonDivisors(ListNode* head)
    {
        ListNode* left = head;
        ListNode* right = head->next;
        while (right) {
            int gcd = getGCD(left->elem, right->elem);
            ListNode* newNode = new ListNode();
            newNode->elem = gcd;
            newNode->next = right;
            left->next = newNode;
            left = right;
            right = right->next;
        }
        return head;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL;
    std::vector<int> nums = { 3, 10, 6, 18 };
    // std::vector<int> nums = { 7 };
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
    refNode = Sol.insertGreatestCommonDivisors(SLL.head);
    while (refNode) {
        std::cout << refNode->elem << std::endl;
        refNode = refNode->next;
    }
    return 0;
}