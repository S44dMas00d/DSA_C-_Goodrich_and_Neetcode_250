#include <iostream>
#include <map>
#include <vector>

using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node()
        : val(0)
        , left(NULL)
        , right(NULL)
        , next(NULL)
    {
    }

    Node(int _val)
        : val(_val)
        , left(NULL)
        , right(NULL)
        , next(NULL)
    {
    }

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val)
        , left(_left)
        , right(_right)
        , next(_next)
    {
    }
};

class Solution {
private:
public:
    int heightHelper(Node* node, map<int, vector<Node*>>& heightAddrMap)
    {
        if (!node) {
            return 0;
        }
        int left = 1 + heightHelper(node->left, heightAddrMap);
        int right = 1 + heightHelper(node->right, heightAddrMap);
        int height = max(left, right);
        if (!heightAddrMap[height].empty() && heightAddrMap[height].back()) {
            heightAddrMap[height].back()->next = node;
        }
        heightAddrMap[height].push_back(node);
        return height;
    }

    Node* connect(Node* node)
    {
        if (!node) {
            return nullptr;
        }
        map<int, vector<Node*>> heightAddrMap;
        int _ = heightHelper(node, heightAddrMap);
        return node;
    }

    void preorderPrint(Node* node, vector<int>& res)
    {
        if (node == nullptr) {
            return;
        }
        res.push_back(node->val);
        preorderPrint(node->left, res);
        preorderPrint(node->right, res);
    }

    void postorderPrint(Node* node, vector<int>& res)
    {
        if (node == nullptr) {
            return;
        }
        postorderPrint(node->left, res);
        postorderPrint(node->right, res);
        res.push_back(node->val);
    }

    void inorderPrint(Node* node, vector<int>& res)
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
    Node one(1);
    Node two(2);
    Node three(3);
    Node four(4);
    Node five(5);
    Node six(6);
    Node seven(7);

    one.left = &two;
    one.right = &three;
    two.left = &four;
    two.right = &five;
    three.left = &six;
    three.right = &seven;

    Node* newTree = Sol.connect(&one);
    vector<int> res;
    Sol.postorderPrint(newTree, res);
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i] << endl;
    }
    cout << endl;

    return 0;
}
