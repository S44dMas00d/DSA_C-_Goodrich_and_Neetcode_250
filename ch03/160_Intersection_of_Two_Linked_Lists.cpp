#include "../common/Singly_Linked_List.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

using ListNode = SNode<int>;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        ListNode* refNode1 = headA;
        ListNode* refNode2 = headB;
        std::unordered_map<ListNode*, int> m;
        if (!refNode1 || !refNode2) {
            return nullptr;
        }
        // first insert all the entries of list 1
        while (refNode1) {
            m.insert({ refNode1, 1 });
            refNode1 = refNode1->next;
        }
        // then iterate and look for them using list 2
        while (refNode2) {
            if (m.count(refNode2)) {
                return refNode2;
            }
            refNode2 = refNode2->next;
        }
        return nullptr;
    }
};

int main()
{
    return 0;
}
