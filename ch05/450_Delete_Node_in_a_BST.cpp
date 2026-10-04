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
public:
    struct findNodeInfo {
        TreeNode* nodePtr;
        TreeNode* ParNodePtr;
        bool isLeftChild;
    };

    void findNodewParent(TreeNode* node, int key, findNodeInfo& findInfoObj)
    {
        if (!node) {
            return;
        }
        if (node->val < key) {
            findNodewParent(node->right, key, findInfoObj);
            if (findInfoObj.nodePtr && !findInfoObj.ParNodePtr) {
                findInfoObj.isLeftChild = false;
                findInfoObj.ParNodePtr = node;
            }
        } else if (node->val > key) {
            findNodewParent(node->left, key, findInfoObj);
            if (findInfoObj.nodePtr && !findInfoObj.ParNodePtr) {
                findInfoObj.isLeftChild = true;
                findInfoObj.ParNodePtr = node;
            }
        }
        if (!findInfoObj.nodePtr && node->val == key) {
            findInfoObj.nodePtr = node;
        }
        return;
    }

    bool isExternal(TreeNode* node)
    {
        return node->left == nullptr && node->right == nullptr;
    }

    TreeNode* deleteNode(TreeNode* root, int key)
    {
        // we now have the parent and the node itself, now we can do deletion
        findNodeInfo findInfoObj { nullptr, nullptr, false };
        findNodewParent(root, key, findInfoObj);
        // auto& [nodePtr, ParNodePtr, isLeftChild] = findInfoObj;
        auto nodePtr = findInfoObj.nodePtr;
        auto ParNodePtr = findInfoObj.ParNodePtr;
        auto isLeftChild = findInfoObj.isLeftChild;
        if (!nodePtr && !ParNodePtr) {
            return root;
        }
        // starting with simpler and then moving to most complex case
        // root node cases:
        // external root node
        if (!ParNodePtr && isExternal(nodePtr)) {
            return nullptr;
        }
        // internal root node
        else if (!ParNodePtr && !nodePtr->left) {
            return nodePtr->right;
        } else if (!ParNodePtr && !nodePtr->right) {
            return nodePtr->left;
        }
        // external node:
        else if (!nodePtr->left && !nodePtr->right) {
            if (isLeftChild)
                ParNodePtr->left = nullptr;
            else
                ParNodePtr->right = nullptr;
        }
        // internal node cases:
        else if (!nodePtr->left && nodePtr->right && !nodePtr->right->right) {
            if (isLeftChild)
                ParNodePtr->left = nodePtr->right;
            else
                ParNodePtr->right = nodePtr->right;
            // ParNodePtr->right = nullptr;
        } else if (nodePtr->left && !nodePtr->right) {
            // FIX 3: dropped "&& !nodePtr->left->left"
            // (it sent some only-left-child nodes into the final else,
            // where nodePtr->right is null -> crash)
            if (isLeftChild)
                ParNodePtr->left = nodePtr->left;
            else
                ParNodePtr->right = nodePtr->left;
        } else if (nodePtr->left && nodePtr->right
            && isExternal(nodePtr->left)
            && isExternal(nodePtr->right)) {
            nodePtr->val = nodePtr->right->val;
            nodePtr->right = nullptr;
        } else {
            TreeNode* exchNode(nullptr);
            TreeNode* parOfExchNode(nullptr);
            // we move the parOfExchNode all the way left of the right subtree of
            // the nodePtr.
            parOfExchNode = nodePtr;
            exchNode = nodePtr->right;
            // FIX 1: removed the "while (!exchNode->left && exchNode->right)" value-swapping
            // loop. It left the key's value in the tree and broke the BST ordering.
            while (exchNode->left) {
                parOfExchNode = exchNode;
                exchNode = exchNode->left;
            }
            if (parOfExchNode->left == exchNode) {
                // exchNode = parOfExchNode->left;
                // now exch values:
                nodePtr->val = exchNode->val;
                // now remove the link to exchNode
                parOfExchNode->left = exchNode->right ? exchNode->right : nullptr;
            } else {
                // exchNode = parOfExchNode->right;
                // now exch values:
                parOfExchNode->val = exchNode->val;
                // now remove the link to exchNode
                parOfExchNode->right = exchNode->right;
                // FIX 2: was exchNode->left (always null here),
                // which dropped exchNode's right subtree
            }
        }
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

    TreeNode N10(10);
    TreeNode N12(12);
    TreeNode N15(15);
    TreeNode N20(20);
    TreeNode N30(30);
    TreeNode N40(40);
    TreeNode N45(45);
    TreeNode N50(50);
    TreeNode N60(60);
    TreeNode N70(70);
    TreeNode N80(80);

    {
        // TreeNode zero(0);
        // TreeNode one(1);
        // TreeNode two(2);
        // TreeNode three(3);
        // TreeNode four(4);
        // TreeNode five(5);
        // TreeNode six(6);
        // TreeNode seven(7);
        // TreeNode eight(8);

        // // Tree # 1:
        // four.left = &two;
        // four.right = &seven;
        // two.left = &one;
        // two.right = &three;

        // // Tree # 2:
        // five.left = &three;
        // five.right = &six;
        // six.right = &seven;
        // three.left = &two;
        // three.right = &four;

        // // Tree # 3:
        // zero.left = nullptr;
        // zero.right = nullptr;

        // Book tree to test what node we get from imbalance
        // checker
        // TreeNode N44(44);
        // TreeNode N17(17);
        // TreeNode N32(32);
        // TreeNode N78(78);
        // TreeNode N50(50);
        // TreeNode N48(48);
        // TreeNode N62(62);
        // TreeNode N54(54);
        // TreeNode N88(88);

        // // Tree # 4:
        // N44.left = &N17;
        // N44.right = &N62;
        // N17.right = &N32;
        // N62.left = &N50;
        // N62.right = &N78;
        // N78.right = &N88;
        // N50.left = &N48;
        // N50.right = &N54;

        // // Tree # 5:
        // N50.left = &N30;
        // N50.right = &N70;
        // N30.right = &N40;
        // N70.left = &N60;
        // N70.right = &N80;

        // // Tree # 6:
        // two.left = &one;
        // two.right = &three;
        // three.right = &five;
        // five.left = &four;
        // five.right = &six;

        // // Tree # 7:
        // three.left = &one;
        // three.right = &four;
        // one.right = &two;

        // // Tree # 8:
        // three.left = &two;
        // three.right = &four;
        // two.left = &one;
    }

    // Tree # 9:
    N20.left = &N10;
    N20.right = &N50;
    N10.right = &N15;
    N15.left = &N12;
    N50.left = &N40;
    N40.right = &N45;

    // TreeNode* root = Sol.deleteNode(&five, 5);
    TreeNode* root = Sol.deleteNode(&N20, 20);

    // Solution::findNodeInfo findInfoObj { nullptr, nullptr, false };
    // Sol.findNodewParent(&N44, 32, findInfoObj);
    // cout << findInfoObj.isLeftChild << endl;
    vector<int> res;
    Sol.inorderPrint(root, res);
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i] << endl;
    }

    return 0;
}