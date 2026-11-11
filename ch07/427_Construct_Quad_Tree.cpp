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
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
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
        vector<vector<int>>& grid, Node*& node)
    {
        int size = BR.x - TL.x;
        if (size < 1) {
            return;
        }
        bool allZeros = true;
        bool allOnes = true;
        for (int y = TL.y; y < BR.y; y++) {
            for (int x = TL.x; x < BR.x; x++) {
                if (grid[y][x] == 1) {
                    allZeros = false;
                    continue;
                }
                if (grid[y][x] == 0) {
                    allOnes = false;
                    // continue;
                }
            }
        }
        if (allZeros || allOnes) {
            node = new Node(allZeros ? false : true, true, nullptr, nullptr, nullptr, nullptr);
            return;
        } else {
            int half = size / 2;
            node = new Node(1, false, nullptr, nullptr, nullptr, nullptr);
            recursiveGridWalk(XY_Coord { TL.x, TL.y }, XY_Coord { TL.x + half, TL.y + half }, grid, node->topLeft);
            recursiveGridWalk(XY_Coord { TL.x + half, TL.y }, XY_Coord { BR.x, TL.y + half }, grid, node->topRight);
            recursiveGridWalk(XY_Coord { TL.x, TL.y + half }, XY_Coord { TL.x + half, BR.y }, grid, node->bottomLeft);
            recursiveGridWalk(XY_Coord { TL.x + half, TL.y + half }, XY_Coord { BR.x, BR.y }, grid, node->bottomRight);
        }
        return;
    }

    Node* construct(vector<vector<int>>& grid)
    {
        Node* root = nullptr;
        XY_Coord TL { 0, 0 };
        XY_Coord BR {
            static_cast<int>(grid[0].size()),
            static_cast<int>(grid.size())
        };
        recursiveGridWalk(TL, BR, grid, root);
        return root;
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
    // std::vector<std::vector<int>> grid = {
    //     { 1, 0 },
    //     { 0, 1 }
    // };

    Node* rootQuadTree = Sol.construct(grid);
    return 0;
}