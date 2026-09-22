#include <iostream>
#include <vector>

using namespace std;
// Definition for a Node.
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode()
        : val(0)
        , left(nullptr)
        , right(nullptr)
    {
    }
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x)
        , left(left)
        , right(right)
    {
    }
};

class Solution {
public:
    void isSameTreeHelper(TreeNode* p, TreeNode* q, bool& isSame)
    {
        if ((p != nullptr && q == nullptr)
            || (p == nullptr && q != nullptr)) {
            isSame = (isSame == false) ? isSame : false;
            return;
        }
        if (p == nullptr && q == nullptr) {
            isSame = (isSame == false) ? isSame : true;
            return;
        }
        if (p->val != q->val) {
            isSame = (isSame == false) ? isSame : false;
            return;
        }
        isSameTreeHelper(p->left, q->left, isSame);
        isSameTreeHelper(p->right, q->right, isSame);
        return;
    }

    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        bool isSame = true;
        isSameTreeHelper(p, q, isSame);
        return isSame;
    }

    void preorderPrint(TreeNode* node, vector<int>& res)
    {
        if (node == nullptr) {
            return;
        }
        res.push_back(node->val);
        preorderPrint(node->left, res);
        preorderPrint(node->right, res);
    }
};

int main()
{
    Solution Sol;
    TreeNode one(1);
    TreeNode two(2);
    TreeNode three(3);
    TreeNode one_(1);
    TreeNode two_(2);
    TreeNode three_(3);

    // Tree 1
    one.left = &two;
    one.right = &three;

    // Tree 2
    one_.left = &two_;
    one_.right = &three_;

    cout << (Sol.isSameTree(&one, &one_) ? "true" : "false") << endl;

    return 0;
}
