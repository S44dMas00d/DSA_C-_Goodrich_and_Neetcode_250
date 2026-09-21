#include <iostream>
#include <vector>

using namespace std;
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() { }

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node*> _children)
    {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    void helper(Node* node, vector<int>& res)
    {
        if (node == nullptr) {
            return;
        }
        for (vector<Node*>::iterator it = node->children.begin();
             it != node->children.end(); ++it) {
            helper(*it, res);
        }
        res.push_back(node->val);
    }

    vector<int> postorder(Node* node)
    {
        vector<int> res;
        helper(node, res);
        return res;
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

    // vector<Node*> children1 = { &three, &two, &four };
    // vector<Node*> children2 = { &five, &six };

    one.children = vector<Node*> { &three, &two, &four };
    three.children = vector<Node*> { &five, &six };

    cout << endl;
    vector<int> res = Sol.postorder(&one);
    for (auto& num : res) {
        cout << num << endl;
    }

    return 0;
}
