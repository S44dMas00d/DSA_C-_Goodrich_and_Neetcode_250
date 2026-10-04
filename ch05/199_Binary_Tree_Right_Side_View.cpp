#include <climits>
#include <iostream>
#include <vector>

using namespace std;
// Definition for a TreeNode.
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
    void inorderRightSideViewHelper(TreeNode* node, int level, vector<int>& res)
    {
        if (!node) {
            return;
        }
        inorderRightSideViewHelper(node->left, level + 1, res);
        while (level >= static_cast<int>(res.size())) {
            res.push_back(0);
        }
        res[level] = node->val;
        inorderRightSideViewHelper(node->right, level + 1, res);
        return;
    }

public:
    vector<int> rightSideView(TreeNode* root)
    {
        vector<int> res;
        inorderRightSideViewHelper(root, 0, res);
        return res; // implicit move for local var
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

    void postorderPrint(TreeNode* node, vector<int>& res)
    {
        if (node == nullptr) {
            return;
        }
        postorderPrint(node->left, res);
        postorderPrint(node->right, res);
        res.push_back(node->val);
    }

    void inorderPrint(TreeNode* node, vector<int>& res)
    {
        if (node == nullptr) {
            return;
        }
        inorderPrint(node->left, res);
        res.push_back(node->val);
        inorderPrint(node->right, res);
    }
};

int main()
{
    Solution Sol;

    TreeNode N1(1);
    TreeNode N2(2);
    TreeNode N3(3);
    TreeNode N4(4);
    TreeNode N5(5);
    TreeNode N6(6);
    TreeNode N7(7);
    TreeNode N8(8);
    TreeNode N9(9);
    TreeNode N10(10);
    TreeNode N11(11);
    TreeNode N12(12);
    TreeNode N13(13);
    TreeNode N14(14);
    TreeNode N15(15);
    TreeNode N16(16);
    TreeNode N17(17);
    TreeNode N18(18);
    TreeNode N19(19);
    TreeNode N20(20);
    TreeNode N30(30);
    TreeNode N40(40);
    TreeNode N45(45);
    TreeNode N50(50);
    TreeNode N60(60);
    TreeNode N70(70);
    TreeNode N80(80);

    // Tree # 1
    N1.right = &N3;
    N1.left = &N2;
    N2.left = &N4;
    N4.left = &N5;

    vector<int> res = Sol.rightSideView(&N1);

    //     vector<int> res;
    // Sol.inorderPrint(&N3, res);
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i] << endl;
    }

    return 0;
}