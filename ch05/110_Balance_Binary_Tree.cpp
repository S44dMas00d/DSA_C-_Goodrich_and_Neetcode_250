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
    int heightOfNode(TreeNode* node, bool& isBal)
    {
        if (node == nullptr) {
            return 0;
        }
        int leftSteps = 1 + heightOfNode(node->left, isBal);
        int rightSteps = 1 + heightOfNode(node->right, isBal);
        int height = max(leftSteps, rightSteps);
        isBal = isBal ? abs(leftSteps - rightSteps) <= 1 : isBal;
        return height;
    }

    bool isBalanced(TreeNode* root)
    {
        bool isBal = true;
        int height = heightOfNode(root, isBal);
        return isBal;
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
    TreeNode four(4);
    TreeNode five(5);
    TreeNode six(6);
    TreeNode seven(7);

    one.left = &two;
    two.left = &three;
    three.left = &four;
    one.right = &five;
    five.right = &six;
    six.right = &seven;

    cout << (Sol.isBalanced(&one) ? "true" : "false") << endl;
    // cout << Sol.heightOfNode(&one) << endl;
    // cout << Sol.diameterOfBinaryTree(&one) << endl;

    return 0;
}
