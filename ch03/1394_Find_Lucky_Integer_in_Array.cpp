#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int findLucky(vector<int>& A)
    {
        // first sort in non-increasing order
        for (size_t i = 1; i < A.size(); i++) {
            int curr = A[i];
            int j = i - 1;
            while ((j >= 0) && (A[j] < curr)) {
                A[j + 1] = A[j];
                j--;
            }
            A[j + 1] = curr;
        }
        // now run the freq checks and stuff:
        int curr_num = A[0];
        int curr_freq = 1;
        for (size_t i = 1; i < A.size(); i++) {
            if (A[i] != curr_num) {
                if (curr_freq == curr_num) {
                    return curr_num;
                }
                curr_num = A[i];
                curr_freq = 1;
            } else {
                curr_freq++;
            }
        }
        if (curr_freq == curr_num) {
            return curr_num;
        }
        return -1;
    }
};

int main()
{
    Solution Sol;
    // vector<int> arr = { 1, 2, 2, 3, 3, 3 };
    vector<int> arr = { 2, 2, 3, 4 };

    int res = Sol.findLucky(arr);
    cout << res << endl;
    return 0;
}