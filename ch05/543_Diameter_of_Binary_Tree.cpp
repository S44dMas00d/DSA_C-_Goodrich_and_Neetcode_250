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
    // int diameterOfBinaryTree(TreeNode* node)
    // {
    //     if (node == nullptr) {
    //         return -1;
    //     }
    //     int stepsLeft = 1 + diameterOfBinaryTree(node->left);
    //     int stepsRight = 1 + diameterOfBinaryTree(node->right);
    //     int diameter = stepsLeft + stepsRight;
    //     // int diameter = min(stepsLeft + stepsRight, diameter);
    //     return max(stepsLeft, stepsRight);
    // }

    // if (node == nullptr) {
    //     return -1;
    // }
    // int diameter = 0;
    // int stepsLeft = 0;
    // int stepsRight = 0;
    // if (node->left == nullptr && node->right == nullptr) {
    //     return 0;
    // }
    // stepsLeft = 1 + diameterOfBinaryTree(node->left);
    // stepsRight = 1 + diameterOfBinaryTree(node->right);
    // diameter = stepsLeft + stepsRight;
    // return diameter;

    int heightOfNode(TreeNode* node)
    {
        if (node == nullptr) {
            // return -1;
            return 0;
        }
        int leftheight = 1 + heightOfNode(node->left);
        int rightheight = 1 + heightOfNode(node->right);
        int height = max(leftheight, rightheight);
        return height;
    }

    void diameterHelper(TreeNode* node, int& diameter)
    {
        int leftHeight = heightOfNode(node->left);
        int rightHeight = heightOfNode(node->right);
        diameter = max(leftHeight + rightHeight, diameter);
    }

    int diameterOfBinaryTree(TreeNode* node)
    {
        if (node == nullptr) {
            return 0;
        }
        int diameter = 0;
        diameter = max(diameterOfBinaryTree(node->left), diameter);
        diameter = max(diameterOfBinaryTree(node->right), diameter);
        diameterHelper(node, diameter);
        return diameter;
    }
    // int diameterOfBinaryTree(TreeNode* node)
    // {
    //     if (node == nullptr) {
    //         return 0;
    //     }
    //     int leftDia = diameterOfBinaryTree(node->left);
    //     int rightDia = diameterOfBinaryTree(node->right);
    //     int diameter = 0;
    //     diameterHelper(node, diameter);
    //     return diameter;
    // }

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

    one.left = &two;
    one.right = &three;
    two.left = &four;
    two.right = &five;

    cout << Sol.heightOfNode(&one) << endl;
    cout << Sol.diameterOfBinaryTree(&one) << endl;

    return 0;
}
