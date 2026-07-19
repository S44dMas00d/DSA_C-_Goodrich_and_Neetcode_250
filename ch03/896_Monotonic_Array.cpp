#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isMonotonic(vector<int>& nums)
    {
        bool is_inc_monotonic = true;
        bool is_dec_monotonic = true;
        int num_size = static_cast<int>(nums.size());
        if (num_size <= 1)
            return true;
        int i = 0;
        int j = 1;
        while ((i < j) && j < num_size) {
            if (nums[i] < nums[j]) {
                is_dec_monotonic = false;
            }
            if (nums[i] > nums[j]) {
                is_inc_monotonic = false;
            }
            i++;
            j++;
        }
        if (is_inc_monotonic || is_dec_monotonic)
            return true;
        return false;
    }
};

int main()
{
    Solution Sol;
    // vector<int> arr = { 1, 2, 2, 3 };
    // vector<int> arr = { 6, 5, 4, 4 };
    vector<int> arr = { 1, 3, 2 };
    bool res = Sol.isMonotonic(arr);
    cout << (res ? "true" : "false") << endl;
    return 0;
}