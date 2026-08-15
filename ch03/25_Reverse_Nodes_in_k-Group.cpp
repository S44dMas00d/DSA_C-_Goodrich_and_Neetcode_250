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
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        ListNode* dummyNode = new ListNode();
        dummyNode->elem = -1;
        dummyNode->next = head;
        ListNode* K = dummyNode;
        ListNode* L = head;
        ListNode* Q = dummyNode;
        ListNode* R = head;
        int rMoves = 0;
        bool reversalLoopAllowed = false;
        bool firstRun = true;
        while (true) {
            R = R ? R->next : R;
            Q = Q->next;
            rMoves++;
            if (rMoves == k) {
                rMoves = 0;
                reversalLoopAllowed = true;
            }
            if (reversalLoopAllowed) {

                while (L != Q) {
                    ListNode* nodeToMove = L;
                    L = L->next;
                    K->next = nodeToMove->next;
                    // K = K->next;
                    nodeToMove->next = Q->next;
                    Q->next = nodeToMove;
                }
                if (firstRun) {
                    head = L;
                    firstRun = false;
                }
                L = R;
                while (K->next != L) {
                    K = K->next;
                }
                while (Q->next != R) {
                    Q = Q->next;
                }
            }
            reversalLoopAllowed = false;
            if (!R) {
                break;
            }
        }
        delete dummyNode;
        return head;
    }
};

int main()
{
    Solution Sol;
    SLinkedList<int> SLL;
    std::vector<int> nums = { 5, 4, 3, 2, 1 };
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
    refNode = Sol.reverseKGroup(SLL.head, 3);
    while (refNode) {
        std::cout << refNode->elem << std::endl;
        refNode = refNode->next;
    }
    std::cout << std::endl;
    return 0;
}
