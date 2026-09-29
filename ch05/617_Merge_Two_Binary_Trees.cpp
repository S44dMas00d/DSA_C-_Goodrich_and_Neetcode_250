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
private:
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2)
    {
        if (!root1 && !root2) {
            return nullptr;
        }
        if (!root1 && root2) {
            return root2;
        }
        if (!root2 && root1) {
            return root1;
        }
        // if (root1 && root2) {
        //     root1->val = root1->val + root2->val;
        //     return root1;
        // }

        root1->left = mergeTrees(root1 ? root1->left : nullptr,
            root2 ? root2->left : nullptr);
        root1->right = mergeTrees(root1 ? root1->right : nullptr,
            root2 ? root2->right : nullptr);
        root1->val = (root1 ? root1->val : 0) + (root2->val ? root2->val : 0);
        return root1;
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
    TreeNode five(5);

    TreeNode one_(1);
    TreeNode two_(2);
    TreeNode three_(3);
    TreeNode four_(4);
    TreeNode seven_(7);

    // Tree 1
    one.left = &three;
    one.right = &two;
    three.left = &five;

    // Tree 2
    two_.left = &one_;
    two_.right = &three_;
    one_.right = &four_;
    three_.right = &seven_;

    TreeNode* newRoot;
    newRoot = Sol.mergeTrees(&one, &two_);

    vector<int> res;
    Sol.preorderPrint(newRoot, res);
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i] << endl;
    }

    return 0;
}
