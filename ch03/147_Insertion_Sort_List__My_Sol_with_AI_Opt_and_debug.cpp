#include "../common/Singly_Linked_List.hpp"
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using ListNode = SNode<int>;

class Solution {
public:
    // Returns true once wallNode has been moved into place, so shallower
    // recursion frames know to stop checking (see Fix #3).
    bool RecursiveBackTrackSwap(ListNode* currNode, ListNode* prevToWallNode, ListNode* wallNode)
    {
        ListNode* temp = currNode;
        currNode = currNode->next;

        // Skip a run of consecutive ascending integers -- but only while doing so
        // is provably safe for THIS wallNode (Fix #1 and #7 below).
        while (currNode && currNode != wallNode && currNode->next && currNode->next != wallNode
            && (currNode->next->elem > currNode->elem)
            && (currNode->next->elem - currNode->elem == 1)
            && (currNode->next->elem <= wallNode->elem)) {
            currNode = currNode->next;
        }

        if (temp == wallNode) {
            return false; // reached wallNode itself: base case, no swap
        }

        bool alreadyMoved = RecursiveBackTrackSwap(currNode, prevToWallNode, wallNode);
        if (alreadyMoved) {
            return true; // a valid insertion point was already found deeper; stop
        }

        // Only commit to this slot if temp is actually a valid anchor
        // (Fix #6): temp <= wallNode < temp->next.
        if (temp->next->elem > wallNode->elem && temp->elem <= wallNode->elem) {
            prevToWallNode->next = wallNode->next;
            wallNode->next = temp->next; // Fix #2: link after temp, not temp->next
            temp->next = wallNode; // Fix #2
            return true;
        }
        return false;
    }

    ListNode* insertionSortList(ListNode* head)
    {
        ListNode* dummy = new ListNode();
        dummy->elem = INT_MIN; // Fix: was -1, which breaks on real negative input
        dummy->next = head;
        head = dummy;

        ListNode* currNode = head;
        ListNode* prevToWallNode = head;
        ListNode* wallNode = head->next;

        while (wallNode) { // Fix #5: was `while (wallNode->next)`, which skipped the tail
            ListNode* saveNext = wallNode->next; // Fix #4: capture BEFORE splicing
            bool moved = RecursiveBackTrackSwap(currNode, prevToWallNode, wallNode);
            if (!moved) {
                prevToWallNode = wallNode; // normal advance
            }
            // if moved==true, prevToWallNode already points at the right predecessor,
            // because the unlink step inside the swap set prevToWallNode->next = saveNext
            wallNode = saveNext;
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
    std::vector<int> nums1 = { 1, 2, 3, 4 };
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