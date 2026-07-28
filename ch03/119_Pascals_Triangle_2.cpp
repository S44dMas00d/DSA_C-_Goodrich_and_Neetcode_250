#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex)
    {
        vector<vector<int>> triangle;
        for (int i = 0; i <= rowIndex; i++) {
            vector<int> row(i + 1, 0);
            for (int j = 0; j <= i; j++) {
                if (i - 1 < 0 || i < 0 || j - 1 < 0 || j == i) {
                    row[j] = 1;
                } else {
                    row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
                }
            }
            triangle.push_back(row);
        }
        return triangle[rowIndex];
    }
};

int main()
{
    Solution Sol;
    vector<int> res = Sol.getRow(3);
    cout << "[";
    for (size_t i = 0; i < res.size(); i++) {
        cout << " " << res[i] << " ";
    }
    cout << "]" << endl;
    return 0;
}