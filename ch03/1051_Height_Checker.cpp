#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    int heightChecker(vector<int>& heights)
    {
        vector<int> sorted_vector = heights;
        if (sorted_vector.size() <= 1) {
            return 0;
        }
        int disorder_count = 0;
        for (size_t i = 1; i < sorted_vector.size(); i++) {
            int curr = sorted_vector[i];
            int j = i - 1;
            while ((j >= 0) && (sorted_vector[j] > curr)) {
                sorted_vector[j + 1] = sorted_vector[j];
                j--;
            }
            sorted_vector[j + 1] = curr;
        }
        for (size_t i = 0; i < sorted_vector.size(); i++) {
            if (heights[i] != sorted_vector[i])
                disorder_count++;
        }

        return disorder_count;
    }
};

int main()
{
    Solution Sol;
    // vector<int> heights = { 1, 1, 4, 2, 1, 3 };
    vector<int> heights = { 5, 1, 2, 3, 4 };

    int res = Sol.heightChecker(heights);
    cout << res << endl;
    return 0;
}