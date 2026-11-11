#include <climits>
#include <iostream>
#include <map>
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
    int heightCheckHelper(TreeNode* node)
    {
        if (!node) {
            return 0;
        }
        int leftHeight = 1 + heightCheckHelper(node->left);
        int rightHeight = 1 + heightCheckHelper(node->right);
        return max(leftHeight, rightHeight);
    }

    int imbalanceCheckHelper(TreeNode* node, TreeNode*& imbalancedNode)
    {
        if (!node) {
            return 0;
        }
        int leftHeight = 1 + imbalanceCheckHelper(node->left, imbalancedNode);
        int rightHeight = 1 + imbalanceCheckHelper(node->right, imbalancedNode);
        // post-order, so the first one found is the lowest unbalanced node
        if (!imbalancedNode && abs(leftHeight - rightHeight) > 1) {
            imbalancedNode = node;
        }
        return max(leftHeight, rightHeight);
    }

    bool restructure(TreeNode* z_par)
    {
        TreeNode* z = heightCheckHelper(z_par->left)
                > heightCheckHelper(z_par->right)
            ? z_par->left
            : z_par->right;
        TreeNode* y = heightCheckHelper(z->left)
                > heightCheckHelper(z->right)
            ? z->left
            : z->right;
        TreeNode* x = heightCheckHelper(y->left)
                > heightCheckHelper(y->right)
            ? y->left
            : y->right;

        bool zWasLeftChild = (z_par->left == z);
        auto attachToZParent = [&](TreeNode* promoted) {
            if (zWasLeftChild) {
                z_par->left = promoted;
            } else {
                z_par->right = promoted;
            }
        };

        if (z->right == y && y->right == x) {
            attachToZParent(y);
            z->right = y->left;
            y->left = z;
            return true;
        } else if (z->left == y && y->left == x) {
            attachToZParent(y);
            z->left = y->right;
            y->right = z;
            return true;
        } else if (z->right == y && y->left == x) {
            attachToZParent(x);
            z->right = x->left;
            y->left = x->right;
            x->left = z;
            x->right = y;
            return true;
        } else if (z->left == y && y->right == x) {
            attachToZParent(x);
            y->right = x->left;
            z->left = x->right;
            x->left = y;
            x->right = z;
            return true;
        }
        return false;
    }

    TreeNode* insertIntoBSTHelper(TreeNode* node, TreeNode* newNode)
    {
        if (!node) {
            return newNode;
        }
        if (node->val > newNode->val) {
            node->left = insertIntoBSTHelper(node->left, newNode);
        } else if (node->val < newNode->val) {
            node->right = insertIntoBSTHelper(node->right, newNode);
        }
        return node;
    }

public:
    TreeNode* insertIntoBST(TreeNode* root, int val)
    {
        TreeNode* newNode = new TreeNode(val);
        // dummy parent so that restructure also works when root is unbalanced
        TreeNode dummy(INT_MAX, root, nullptr);
        // first we insert the new node
        dummy.left = insertIntoBSTHelper(dummy.left, newNode);
        // then we find out if the tree got imbalanced and where
        TreeNode* imbalancedNode = nullptr;
        imbalanceCheckHelper(dummy.left, imbalancedNode);
        // finally we apply rebalance on it till its not required
        while (imbalancedNode) {
            // restructure wants the parent of the imbalanced node
            TreeNode* par = &dummy;
            while (par->left != imbalancedNode && par->right != imbalancedNode) {
                par = imbalancedNode->val < par->val ? par->left : par->right;
            }
            restructure(par);
            imbalancedNode = nullptr;
            imbalanceCheckHelper(dummy.left, imbalancedNode);
        }

        return dummy.left;
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
    four.left = &two;
    four.right = &seven;
    two.left = &one;
    two.right = &three;

    // Tree # 2:
    // four.left = &two;
    // four.right = &seven;
    // two.right = &three;
    // three.left = &one;

    // Book tree to test what node we get from imbalance
    // checker
    TreeNode N44(44);
    TreeNode N17(17);
    TreeNode N32(32);
    TreeNode N78(78);
    TreeNode N50(50);
    TreeNode N48(48);
    TreeNode N62(62);
    TreeNode N54(54);
    TreeNode N88(88);

    // Tree # 3
    N44.left = &N17;
    N44.right = &N78;
    N17.right = &N32;
    N78.left = &N50;
    N78.right = &N88;
    N50.left = &N48;
    N50.right = &N62;
    // N62.left = &N54;

    TreeNode* newTree = Sol.insertIntoBST(&N44, 54);
    vector<int> res;
    Sol.inorderPrint(newTree, res);
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i] << endl;
    }
    cout << endl;

    return 0;
}
