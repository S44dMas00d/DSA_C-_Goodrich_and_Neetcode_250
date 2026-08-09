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
    void RecursiveBackTrackSwap(ListNode* currNode, ListNode* wallNode)
    {
        ListNode* temp = currNode;
        currNode = currNode->next;
        if (temp == wallNode) {
            return;
        }
        RecursiveBackTrackSwap(currNode, wallNode);
        // Now that the walk back covers all nodes in
        // rear walk fashion - we can proceed with swaps
        // the swap must be honored between temp.next and wallnode.
        if (temp->next->elem > wallNode->elem) {
            ListNode* old = temp->next;
            temp->next = wallNode;
            old->next = wallNode->next;
            wallNode->next = old;
        }
        // std::cout << "this stack: " << std::endl;
        // std::cout << "temp: " << temp->elem << std::endl;
        // std::cout << "curr: " << currNode->elem << std::endl;
        // std::cout << "wall: " << wallNode->elem << std::endl;
        // std::cout << std::endl;
    }

    ListNode* insertionSortList(ListNode* head)
    {
        ListNode* dummy = new ListNode();
        dummy->elem = -1;
        dummy->next = head;
        head = dummy;
        ListNode* wallNode = head;
        ListNode* currNode = head;
        while (wallNode) {
            RecursiveBackTrackSwap(currNode, wallNode);
            wallNode = wallNode->next;
        }
        head = dummy->next;
        dummy->next = nullptr;
        delete dummy;
        return head;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL1;
    // std::vector<int> nums1 = { 3, 1, 2, 4 };
    std::vector<int> nums1 = { 3, 1, 2, 4 };
    // std::vector<int> nums1 = { 4, 2, 1 };
    for (size_t i = 0; i < nums1.size(); i++) {
        SLL1.addFront(nums1[i]);
    }
    ListNode* refNode1 = SLL1.head;
    std::cout << "SLL1: " << std::endl;
    while (refNode1) {
        std::cout << refNode1->elem << std::endl;
        refNode1 = refNode1->next;
    }
    ListNode* refNodeRes = Sol.insertionSortList(SLL1.head);
    std::cout << "New List: " << std::endl;
    while (refNodeRes) {
        std::cout << refNodeRes->elem << std::endl;
        refNodeRes = refNodeRes->next;
    }
    std::cout << std::endl;
    return 0;
}
