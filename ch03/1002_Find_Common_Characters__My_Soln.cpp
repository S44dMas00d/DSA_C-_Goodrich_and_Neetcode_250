#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    struct entry {
        int count;
        bool isMutated;
    };

    vector<string> commonChars(vector<string>& words)
    {
        std::unordered_multimap<char, entry> charCountBook;
        vector<string> res;
        for (size_t j = 0; j < words.size(); ++j) {
            std::unordered_multimap<char, entry>::iterator p;
            string word = words[j];
            for (size_t i = 0; i < word.size(); ++i) {
                // if this character isn't already in the map
                if (j == 0 && charCountBook.find(word[i]) == charCountBook.end()) {
                    charCountBook.insert({ word[i], entry { count : 1, isMutated : true } });
                    continue;
                } else {
                    // p = charCountBook.find(word[i]);
                    p = charCountBook.end();
                    for (p = charCountBook.begin(); p != charCountBook.end(); ++p) {
                        if (p->first == word[i] && p->second.isMutated == false) {
                            break;
                        }
                    }
                    if (j == 0 && p == charCountBook.end()) {
                        charCountBook.insert({ word[i], entry { count : 1, isMutated : true } });
                    } else if (p != charCountBook.end()) {
                        p->second.count += 1;
                        p->second.isMutated = true;
                    }
                }
            }

            for (p = charCountBook.begin(); p != charCountBook.end();) {
                if (p->second.count < static_cast<int>(j)) {
                    p = charCountBook.erase(p);
                } else {
                    ++p;
                }
            }

            for (p = charCountBook.begin(); p != charCountBook.end(); ++p) {
                p->second.isMutated = false;
            }
        }
        for (auto p = charCountBook.begin(); p != charCountBook.end(); ++p) {
            if (p->second.count >= static_cast<int>(words.size())) {
                res.push_back(string(1, p->first));
            }
        }
        return res;
    }
};

int main()
{
    Solution* Sol = new Solution();
    vector<string> words = { "bbddabab", "cbcddbdd", "bbcadcab", "dabcacad", "cddcacbc", "ccbdbcba", "cbddaccc", "accdcdbb" };
    vector<string> res;
    res = Sol->commonChars(words);
    cout << "[";
    for (size_t i = 0; i < res.size(); ++i)
        cout << " " << res[i] << " ";
    cout << "]" << endl;
}
