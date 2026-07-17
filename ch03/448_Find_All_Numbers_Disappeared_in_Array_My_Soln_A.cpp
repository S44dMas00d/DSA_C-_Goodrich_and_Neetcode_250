#include <cmath>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums)
    {
        vector<int> res;
        std::unordered_set<int> my_set(nums.begin(), nums.end());
        for (int i = 1; i <= static_cast<int>(nums.size()); i++) {
            if (my_set.find(i) == my_set.end()) {
                res.push_back(i);
            }
        }
        return res;
    }
};

int main()
{
    return 0;
}