#include <climits>
#include <iostream>
#include <list>
#include <vector>

using namespace std;
// Definition for a Node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node()
    {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
private:
public:
    struct XY_Coord {
        int x;
        int y;
    };

    void recursiveGridWalk(XY_Coord TL, XY_Coord BR,
        vector<vector<int>>& grid)
    {
        int size = BR.x - TL.x;
        if (size < 1) {
            return;
        }
        for (int y = TL.y; y < BR.y; y++) {
            for (int x = TL.x; x < BR.x; x++) {
                cout << grid[y][x] << " ";
            }
            cout << endl;
        }
        cout << endl;
        if (size == 1) {
            return;
        }
        int half = size / 2;
        for (int y = TL.y; y < BR.y; y += half) {
            for (int x = TL.x; x < BR.x; x += half) {
                recursiveGridWalk(XY_Coord { x, y }, XY_Coord { x + half, y + half }, grid);
            }
        }
    }

    Node* construct(vector<vector<int>>& grid)
    {
    }
};

int main()
{
    Solution Sol;
    std::vector<std::vector<int>> grid = {
        { 1, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 0, 0, 0, 0 }
    };

    Solution::XY_Coord TL { 0, 0 };
    Solution::XY_Coord BR {
        static_cast<int>(grid[0].size()),
        static_cast<int>(grid.size())
    };

    Sol.recursiveGridWalk(TL, BR, grid);
    return 0;
}