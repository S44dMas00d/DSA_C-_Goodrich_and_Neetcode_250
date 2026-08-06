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
    ListNode* rotateRight(ListNode* head, int k)
    {
        auto recurseStitch = [&](auto&& self, ListNode* curr) {
            if (!curr || !curr->next) {
                return;
            }
            ListNode* temp = curr;
            curr = curr->next;
            self(self, curr);
            if (k > 0) {
                ListNode* old = head;
                temp->next = nullptr;
                head = curr;
                head->next = old;
                k--;
            }
        };
        // counting number of nodes to avoid extra rotations
        int num_nodes = 0;
        ListNode* ref = head;
        while (ref) {
            num_nodes++;
            ref = ref->next;
        }
        k = num_nodes > 0 ? k % num_nodes : 0;
        while (k > 0 && head && head->next) {
            recurseStitch(recurseStitch, head);
        }
        return head;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL1;
    // std::vector<int> nums1 = { 5, 4, 3, 2, 1 };
    std::vector<int> nums1 = { 2, 1, 0 };
    // std::vector<int> nums1 = { 1 };
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
    ListNode* refNodeRes = Sol.rotateRight(SLL1.head, 4);
    while (refNodeRes) {
        std::cout << refNodeRes->elem << std::endl;
        refNodeRes = refNodeRes->next;
    }
    std::cout << std::endl;
    return 0;
}
