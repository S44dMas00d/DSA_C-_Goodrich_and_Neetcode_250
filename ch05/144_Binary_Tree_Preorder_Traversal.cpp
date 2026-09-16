#include <iostream>
#include <vector>

using namespace std;
//   Definition for a binary tree node.
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
    void preorderHelper(TreeNode* root, vector<int>& cumulative_array)
    {
        if (!root) {
            return;
        };
        cumulative_array.push_back(root->val);
        preorderHelper(root->left, cumulative_array);
        preorderHelper(root->right, cumulative_array);
        return;
    }

    vector<int> preorderTraversal(TreeNode* root)
    {
        vector<int> res;
        preorderHelper(root, res);
        return res;
    }
};

int main()
{
    Solution Sol;
    TreeNode root(1);
    TreeNode two(2);
    TreeNode three(3);

    root.right = &two;
    two.left = &three;
    // case assumed made here
    TreeNode* temp = &root;
    vector<int> res = Sol.preorderTraversal(temp);
    for (vector<int>::iterator it = res.begin(); it != res.end(); ++it) {
        cout << *it << endl;
    }
    return 0;
}
