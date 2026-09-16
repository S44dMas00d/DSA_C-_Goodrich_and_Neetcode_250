#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//  Definition for a binary tree node.
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
    int maxDepth(TreeNode* root)
    {
        if (!root) {
            return 0;
        }
        int l = 1 + maxDepth(root->left);
        int r = 1 + maxDepth(root->right);
        return max(l, r);
    }
};

int main()
{
    Solution Sol;
    TreeNode root3(3);
    TreeNode n9(9);
    TreeNode n20(20);
    TreeNode n15(15);
    TreeNode n7(7);

    root3.left = &n9;
    root3.right = &n20;
    n20.left = &n15;
    n20.right = &n7;
    // case assumed made here
    TreeNode* temp = &root3;
    int res = Sol.maxDepth(temp);
    cout << res << endl;

    return 0;
}
