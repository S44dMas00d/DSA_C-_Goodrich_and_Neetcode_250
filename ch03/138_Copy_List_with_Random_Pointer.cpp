#include <iostream>
#include <utility>
#include <vector>

// Definition for a Node.
class Node {
public:
    int val;
    Node* random;
    Node* next;

    Node(int _val)
    {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head)
    {

        if (!head) {
            return head;
        }
        // the head of the old LL
        Node* head1 = head;
        // the head of the new LL
        Node* head2 = nullptr;
        Node* currOld = head;
        Node* currNew = head;

        // we need to make the interleaved linked list
        // combined with old and new nodes and shaped out
        // like a zipper with old->new->old->new nodes
        while (currOld) {
            Node* newNode = new Node(currOld->val);
            newNode->next = currOld->next;
            currOld->next = newNode;
            currOld = newNode->next;
        }
        // now we have the interleaved list we need to setup the
        // random pointers of the newNodes in the interleaved list
        currOld = head;
        currNew = head->next;
        while (currOld) {
            currNew->random = currOld->random ? currOld->random->next : nullptr;
            currOld = currOld->next->next;
            currNew = currOld ? currOld->next : nullptr;
        }
        // now that we have the randoms sorted, we need to separate both lists
        head1 = head;
        currOld = head;
        head2 = head->next;
        currNew = head->next;
        while (currOld) {
            currOld->next = currOld->next->next;
            currNew->next = currNew->next ? currNew->next->next : nullptr;
            currOld = currOld->next;
            currNew = currOld ? currOld->next : nullptr;
        }
        return head2;
    }
};

int main()
{
    Solution Sol;
    // std::vector<std::pair<int, int>> nums = { { 7, -1 }, { 13, 0 }, { 11, 4 }, { 10, 2 }, { 1, 0 } };
    std::vector<std::pair<int, int>> nums = { { -1, -1 } };
    std::vector<Node*> pointerAgainstIndex(nums.size());
    Node* head = nullptr;
    Node* curr = nullptr;
    for (size_t i = 0; i < nums.size(); i++) {
        if (i == 0) {
            head = new Node(nums[i].first);
            pointerAgainstIndex[0] = head;
            curr = head;
            continue;
        }
        Node* newNode = new Node(nums[i].first);
        pointerAgainstIndex[i] = newNode;
        curr->next = newNode;
        curr = curr->next;
    }
    curr = head;
    for (size_t i = 0; i < nums.size(); i++) {
        if (nums[i].second == -1) {
            curr->random = nullptr;
            curr = curr->next;
            continue;
        }
        curr->random = pointerAgainstIndex[nums[i].second];
        curr = curr->next;
    }
    curr = head;
    std::cout << "-1 means NULL in following" << std::endl;
    std::cout << "The Original List: " << std::endl;
    while (curr) {
        std::cout << "curr.val -> " << curr->val << " || curr.random.val -> " << (curr->random ? curr->random->val : -1) << std::endl;
        curr = curr->next;
    }

    std::cout << std::endl;
    std::cout << "Now the Copied List: " << std::endl;
    // Now that we have done all this heavy lifting besides the question - lets proceed to
    // developing the actual solution
    Node* head2 = Sol.copyRandomList(head);
    Node* curr2 = head2;
    while (curr2) {
        std::cout << "curr.val -> " << curr2->val << " || curr.random.val -> " << (curr2->random ? curr2->random->val : -1) << std::endl;
        curr2 = curr2->next;
    }
    // REMEMBER DELETING THE NODES OF BOTH LISTS.
    curr = head;
    curr2 = head2;

    while (curr) {
        Node* old = curr;
        curr = old->next;
        delete old;
    }

    while (curr2) {
        Node* old = curr2;
        curr2 = old->next;
        delete old;
    }
    std::cout << std::endl;
    return 0;
}
