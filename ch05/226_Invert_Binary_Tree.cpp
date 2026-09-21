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
    TreeNode* invertTree(TreeNode* node)
    {
        if (node == nullptr) {
            return node;
        }
        TreeNode* left = invertTree(node->left);
        TreeNode* right = invertTree(node->right);

        node->right = left;
        node->left = right;
        return node;
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
    TreeNode seven(7);
    TreeNode six(6);
    TreeNode nine(9);

    four.left = &two;
    two.left = &one;
    two.right = &three;
    four.right = &seven;
    seven.left = &six;
    seven.right = &nine;

    cout << endl;
    //  res = Sol.invertTree();
    vector<int> currVec;
    Sol.preorderPrint(&four, currVec);
    for (vector<int>::iterator it = currVec.begin();
         it != currVec.end(); ++it) {
        cout << *it << endl;
    }

    cout << endl;
    // now for the inversion
    Sol.invertTree(&four);
    vector<int> newVec;
    Sol.preorderPrint(&four, newVec);
    for (vector<int>::iterator it = newVec.begin();
         it != newVec.end(); ++it) {
        cout << *it << endl;
    }

    return 0;
}
