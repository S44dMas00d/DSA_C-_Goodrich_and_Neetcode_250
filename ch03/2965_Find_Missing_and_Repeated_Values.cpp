#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid)
    {
        vector<int> flat_vector;
        for (size_t i = 0; i < grid.size(); ++i) {
            // for (size_t j = 0; j < grid[i].size(); ++j) {
            //     // grid[i][j]
            // }
            flat_vector.insert(flat_vector.end(), grid[i].begin(), grid[i].end());
        }
        int outer_size = static_cast<int>(grid.size());
        int inner_size = static_cast<int>(grid[0].size());
        int flat_arr_size = outer_size * inner_size;
        vector<int> freq(flat_arr_size + 1, 0);
        for (int i = 0; i < flat_arr_size; i++) {
            freq[flat_vector[i]]++;
        }
        vector<int> ans { 0, 0 };
        for (int i = 1; i <= flat_arr_size; i++) {
            if (freq[i] == 2)
                ans[0] = i;
            else if (freq[i] == 0)
                ans[1] = i;
        }
        return ans;
    }
};

int main()
{
    Solution Sol;
    std::vector<std::vector<int>> grid = {
        { 9, 1, 7 },
        { 8, 9, 2 },
        { 3, 4, 6 }
    };
    vector<int> ans;
    ans = Sol.findMissingAndRepeatedValues(grid);
    cout << "[ ";
    for (int i = 0; i < static_cast<int>(ans.size()); i++) {
        cout << " " << ans[i] << " ";
    }
    cout << "]" << endl;
    return 0;
}