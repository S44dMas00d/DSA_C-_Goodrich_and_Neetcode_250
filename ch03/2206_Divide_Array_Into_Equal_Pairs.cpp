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
        int i = 0;
        int j = 0;
        // first we need to sort it
        for (i = 1; i < num_size; i++) {
            int curr = nums[i];
            j = i - 1;
            while ((j >= 0) && (nums[j] > curr)) {
                nums[j + 1] = nums[j];
                j--;
            }
            nums[j + 1] = curr;
        }
        int pair_count = 0;
        int expected_num_pairs = num_size / 2;
        // now we need to do sliding window:
        i = 0;
        j = 1;
        while ((i < j) && (j < num_size)) {
            if (nums[i] == nums[j]) {
                i = i + 2;
                j = j + 2;
                pair_count++;
            } else {
                i++;
                j++;
            }
        }
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