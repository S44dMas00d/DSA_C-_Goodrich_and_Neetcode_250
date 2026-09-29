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
    void isSubtreeHelper(TreeNode* root, TreeNode* subRoot, bool& isSub, bool& isCrossed)
    {
        if (root == nullptr && subRoot == nullptr) {
            return;
        }
        if (root == nullptr && subRoot != nullptr) {
            isSub = false;
            return;
        }
        if (root != nullptr && subRoot == nullptr) {
            isSub = false;
            return;
        }
        if (root->val != subRoot->val) {
            isSub = (isSub && isCrossed) ? true : false;
        }
        if (root->val == subRoot->val
            && ((root->left == nullptr && subRoot->left == nullptr) || ((root->left && subRoot->left) && root->left->val == subRoot->left->val))
            && ((root->right == nullptr && subRoot->right == nullptr) || ((root->right && subRoot->right) && root->right->val == subRoot->right->val))) {

            // isSub = (isSub == false) ? false : true;
            isSub = true;
        }
        // if (root->val == subRoot->val
        //     && ((root->left && subRoot->left) ? root->left->val == subRoot->left->val : true)
        //     && ((root->right && subRoot->right) ? root->right->val == subRoot->right->val : true)) {
        //     // isSub = (isSub == false) ? false : true;
        //     isSub = true;
        // }

        isSubtreeHelper(root->left, isSub ? subRoot->left : subRoot, isSub, isCrossed);
        // bool isCrossed = true;
        isSubtreeHelper(root->right, isSub ? subRoot->right : subRoot, isSub, isCrossed);
        isCrossed = true;
        return;
    }

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot)
    {
        bool isSub = false;
        bool isCrossed = false;
        isSubtreeHelper(root, subRoot, isSub, isCrossed);
        return isSub;
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
    TreeNode zero(0);
    TreeNode one(1);
    TreeNode two(2);
    TreeNode three(3);
    TreeNode four(4);
    TreeNode five(5);

    TreeNode one_(1);
    TreeNode two_(2);
    TreeNode four_(4);
    // Tree 1
    three.left = &four;
    three.right = &five;
    four.left = &one;
    four.right = &two;
    // two.left = &zero;

    // Tree 2
    four_.left = &one_;
    four_.right = &two_;

    // cout << (Sol.isSubtree(&three, &four_) ? "true" : "false") << endl;

    TreeNode ONE(1);
    TreeNode ONE_(1);
    TreeNode ONE__(1);
    // tree 1
    ONE.left = &ONE_;
    // tree 2
    // ONE__
    cout << (Sol.isSubtree(&ONE, &ONE__) ? "true" : "false") << endl;

    return 0;
}
