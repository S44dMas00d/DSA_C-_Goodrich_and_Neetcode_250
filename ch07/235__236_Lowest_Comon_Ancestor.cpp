#include <iostream>
#include <map>
#include <vector>

using namespace std;
// Definition for a TreeNode.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {
    }
};

class Solution {
private:
    struct p_q_nodes_info {
        bool p_seen;
        bool q_seen;
    };

    void LCATraversalHelper(TreeNode* node,
        TreeNode* p, TreeNode* q, p_q_nodes_info& pqInfo,
        std::vector<TreeNode*>& nodeStack,
        std::vector<TreeNode*>& pPath,
        std::vector<TreeNode*>& qPath)
    {
        if (!node) {
            return;
        }
        nodeStack.push_back(node);
        LCATraversalHelper(node->left, p, q, pqInfo, nodeStack, pPath, qPath);
        LCATraversalHelper(node->right, p, q, pqInfo, nodeStack, pPath, qPath);
        if (!pqInfo.p_seen) {
            pqInfo.p_seen = node == p;
            pPath = std::vector<TreeNode*>(nodeStack);
        }
        if (!pqInfo.q_seen) {
            pqInfo.q_seen = node == q;
            qPath = std::vector<TreeNode*>(nodeStack);
        }
        nodeStack.pop_back();
        return;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        std::vector<TreeNode*> nodeStack;
        std::vector<TreeNode*> pPath;
        std::vector<TreeNode*> qPath;
        TreeNode* LCA = nullptr;
        p_q_nodes_info pqInfo { false, false };
        LCATraversalHelper(root, p, q, pqInfo, nodeStack, pPath, qPath);
        for (size_t i = 0; i < pPath.size() && i < qPath.size() && pPath[i] == qPath[i]; ++i) {
            LCA = pPath[i];
        }
        return LCA;
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
    TreeNode zero(0);
    TreeNode one(1);
    TreeNode two(2);
    TreeNode three(3);
    TreeNode four(4);
    TreeNode five(5);
    TreeNode six(6);
    TreeNode seven(7);
    TreeNode eight(8);

    // Tree # 1:
    // three.left = &five;
    // three.right = &one;
    // five.left = &six;
    // five.right = &two;
    // two.left = &seven;
    // two.right = &four;
    // one.left = &zero;
    // one.right = &eight;

    // Tree # 2:
    one.left = &two;
    one.right = &three;
    two.right = &four;

    // TreeNode* newTree = Sol.connect(&one);
    // vector<int> res;
    // Sol.inorderPrint(&three, res);
    // for (size_t i = 0; i < res.size(); i++) {
    //     cout << res[i] << endl;
    // }
    cout << endl;
    TreeNode* resNode
        = Sol.lowestCommonAncestor(&one, &four, &three);
    cout << resNode->val << endl;
    return 0;
}
