#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool check(vector<int>& nums)
    {
        if (nums.size() <= 1) {
            return true;
        }
        vector<int> result;
        vector<int>::iterator iter_inv;
        int last_num = nums[0];
        for (iter_inv = nums.begin(); iter_inv != nums.end(); ++iter_inv) {
            if (*iter_inv < last_num) {
                break;
            }
            last_num = *iter_inv;
        }
        result.insert(result.end(), iter_inv, nums.end());
        result.insert(result.end(), nums.begin(), iter_inv);
        for (size_t i = 1; i < nums.size(); i++) {
            int diff = result[i] - result[i - 1];
            if (diff > 1) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution Sol;
    // vector<int> arr = { 3, 4, 5, 1, 2 };
    vector<int> arr = { 2, 1, 3, 4 };
    // vector<int> arr = { 1, 2, 3 };
    bool res = Sol.check(arr);
    cout << (res ? "true" : "false") << endl;
    return 0;
}