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
    void reverseOddLevelsHelper(TreeNode* node, int depth, vector<vector<TreeNode*>>& nodePtrLevelsVec)
    {
        if (!node) {
            return;
        }
        if (depth >= static_cast<int>(nodePtrLevelsVec.size())) {
            nodePtrLevelsVec.push_back({});
        }
        nodePtrLevelsVec[depth].push_back(node);
        reverseOddLevelsHelper(node->left, depth + 1, nodePtrLevelsVec);
        reverseOddLevelsHelper(node->right, depth + 1, nodePtrLevelsVec);
        return;
    }

    TreeNode* reverseOddLevels(TreeNode* root)
    {
        vector<vector<TreeNode*>> result;
        reverseOddLevelsHelper(root, 0, result);
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                {
                    cout << result[i][j]->val << endl;
                }
            }
        }
        cout << endl;
        for (size_t k = 0; k < result.size(); k++) {
            if (static_cast<int>(k) % 2 == 0) {
                continue;
            }
            size_t i = 0;
            size_t j = result[k].size() - 1;
            while (i < j) {
                int temp = result[k][i]->val;
                result[k][i]->val = result[k][j]->val;
                result[k][j]->val = temp;
                i++;
                j--;
            }
        }
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                {
                    cout << result[i][j]->val << endl;
                }
            }
        }
        cout << endl;

        return root;
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

    TreeNode N2(2);
    TreeNode N3(3);
    TreeNode N5(5);
    TreeNode N8(8);
    TreeNode N13(13);
    TreeNode N21(21);
    TreeNode N34(34);

    // Tree # 1:
    N2.left = &N3;
    N2.right = &N5;
    N3.left = &N8;
    N3.right = &N13;
    N5.left = &N21;
    N5.right = &N34;

    TreeNode* resRootNode = Sol.reverseOddLevels(&N2);

    vector<int> res;
    Sol.preorderPrint(resRootNode, res);
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i] << endl;
    }

    return 0;
}