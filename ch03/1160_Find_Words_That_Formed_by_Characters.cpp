#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int countCharacters(vector<string>& words, string chars)
    {
        int resulting_count = 0;
        // first make a global unordered map to check against for occurrences
        unordered_map<char, int> given_char_map;
        for (size_t i = 0; i < chars.size(); i++) {
            char c = chars[i];
            unordered_map<char, int>::iterator it = given_char_map.find(c);
            if (it != given_char_map.end()) {
                // found
                int value = it->second;
                it->second = value + 1;
            } else {
                // not found
                given_char_map.insert({ c, 1 });
            }
        }
        // then we do the same for each word in words
        for (size_t i = 0; i < words.size(); i++) {
            string word = words[i];
            unordered_map<char, int> local_word_map;
            for (size_t j = 0; j < word.size(); j++) {
                char c = word[j];

                unordered_map<char, int>::iterator it = local_word_map.find(c);

                if (it != local_word_map.end()) {
                    // Found
                    int value = it->second;
                    it->second = value + 1;
                } else {
                    // Not found
                    local_word_map.insert({ c, 1 });
                }
            }
            bool all_chars_found = true;
            for (unordered_map<char, int>::iterator it = local_word_map.begin();
                 it != local_word_map.end(); ++it) {
                char local_char = it->first;
                int local_char_count = it->second;
                unordered_map<char, int>::iterator g_it = given_char_map.find(local_char);
                if (g_it == given_char_map.end() || g_it->second < local_char_count) {
                    all_chars_found = false;
                }
            }
            if (all_chars_found) {
                resulting_count += static_cast<int>(word.size());
            }
        }
        return resulting_count;
    }
};

int main()
{
    Solution Sol;
    vector<string> words = { "cat", "bt", "hat", "tree" };
    string chars = "atach";
    int res = Sol.countCharacters(words, chars);
    cout << res << endl;
    /* code */
    return 0;
}
