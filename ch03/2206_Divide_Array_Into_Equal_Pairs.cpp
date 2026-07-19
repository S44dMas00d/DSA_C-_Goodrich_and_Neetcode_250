#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool divideArray(vector<int>& nums)
    {
        int num_size = static_cast<int>(nums.size());
        if (num_size % 2 != 0 && num_size <= 1) {
            return false;
        }
        auto findInVector = [](const std::vector<int>& v, int value) {
            for (auto iter = v.begin(); iter != v.end(); ++iter) {
                if (*iter == value)
                    return true;
            }
            return false;
        };
        int pair_count = 0;
        int i = 0;
        int j = 1;
        vector<int> last_pair_i_s;
        vector<int> last_pair_j_s;
        bool pair_checked = false;
        while ((i < j) && j < num_size) {
            if (nums[i] == nums[j]) {
                pair_checked = true;
                pair_count++;
            }
            if (pair_checked) {
                if (findInVector(last_pair_j_s, i + 1)) {
                    last_pair_i_s.push_back(i);
                    i = last_pair_j_s.back() + 1;
                    if (i == j) {
                        i++;
                    }
                } else {
                    last_pair_i_s.push_back(i);
                    i++;
                }
                last_pair_j_s.push_back(j);
                j = i + 1;
            } else {
                pair_checked = false;
                j++;
            }
        }
        int expected_num_pairs = num_size / 2;
        return expected_num_pairs == pair_count;
    }
};

int main()
{
    Solution Sol;
    // vector<int> nums = { 3, 2, 3, 2, 2, 2 };
    vector<int> nums = { 9, 4, 18, 3, 2, 6, 18, 15, 7, 15, 6, 4, 15, 14, 7, 4, 15, 4, 3, 17, 9, 13, 13, 12, 2, 14, 12, 17 };
    bool res = Sol.divideArray(nums);
    cout << (res ? "true" : "false") << endl;
    return 0;
}