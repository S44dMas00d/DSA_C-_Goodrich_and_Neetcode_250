#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isArraySpecial(vector<int>& nums)
    {
        int arr_size = static_cast<int>(nums.size());
        if (arr_size <= 1) {
            return true;
        }
        // sliding window - fixed - use while loop
        int i = 0;
        int j = 1;
        while ((i < j) && (j < arr_size)) {
            int diff = abs(nums[j] - nums[i]);
            if (diff % 2 == 0) {
                return false;
            }
            i++;
            j++;
        }
        return true;
    }
};

int main()
{
    Solution Sol;
    // vector<int> arr = { 4, 3, 1, 6 };
    // vector<int> arr = { 2, 1, 4 };
    vector<int> arr = { 1 };
    bool res = Sol.isArraySpecial(arr);
    cout << (res ? "true" : "false") << endl;
}
