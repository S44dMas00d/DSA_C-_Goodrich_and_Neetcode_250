#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int checkGood(int i, int j, int sum, vector<int>& nums)
    {
        int n = static_cast<int>(nums.size());

        // done: i has walked off the end
        if (i >= n) {
            return sum;
        }

        // j walked off the end -> move to next i, restart j at i+1
        if (j >= n) {
            return checkGood(i + 1, i + 2, sum, nums);
        }

        if (nums[i] == nums[j]) {
            sum++;
        }

        // advance j, keep i fixed
        return checkGood(i, j + 1, sum, nums);
    }

    int numIdenticalPairs(vector<int>& nums)
    {
        if (nums.size() < 2) {
            return 0;
        }
        return checkGood(0, 1, 0, nums);
    }
};

int main()
{
    Solution Sol;
    vector<int> nums = { 1, 1, 1, 1 };
    // vector<int> nums = { 1, 2, 3, 1, 1, 3 };
    int num_pairs = Sol.numIdenticalPairs(nums);
    cout << num_pairs << endl; // prints 6
}