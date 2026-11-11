#include <iostream>
#include <vector>

using namespace std;
// Definition for a Node.
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
    void rangeSumBSTHelper(TreeNode* root, int& low, int& high, int& res)
    {
        if (!root) {
            return;
        }
        res += (root->val <= high && root->val >= low) ? root->val : 0;
        rangeSumBSTHelper(root->left, low, high, res);
        rangeSumBSTHelper(root->right, low, high, res);
        return;
    }

public:
    int rangeSumBST(TreeNode* root, int low, int high)
    {
        int res = 0;
        rangeSumBSTHelper(root, low, high, res);
        return res;
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
    void inorderPrint(TreeNode* node, vector<int>& res)
    {
        if (node == nullptr) {
            return;
        }
        preorderPrint(node->left, res);
        res.push_back(node->val);
        preorderPrint(node->right, res);
    }
};

int main()
{
    Solution Sol;
    TreeNode ten(10);
    TreeNode five(5);
    TreeNode fifteen(15);
    TreeNode three(3);
    TreeNode seven(7);
    TreeNode eighteen(18);

    // Tree 1
    ten.left = &five;
    ten.right = &fifteen;
    five.left = &three;
    five.right = &seven;
    fifteen.right = &eighteen;

    vector<int> res;
    Sol.preorderPrint(&ten, res);
    // for (size_t i = 0; i < res.size(); i++) {
    //     cout << res[i] << endl;
    // }
    int sum = Sol.rangeSumBST(&ten, 7, 15);
    cout << sum << endl;
    return 0;
}
