class Solution {
    bool checkVowel(char c) {
        return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    }
public:
    Solution() {
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
    }
#ifndef OPTIMAL
    // 4 ms Beats 81.49%
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        vector<int> ans(queries.size());
        vector<int> prefix(words.size() + 1, 0);
        for (int i = 1; i <= words.size(); ++i) {
            prefix[i] = prefix[i - 1];
            if (checkVowel(words[i - 1][0]) && checkVowel(words[i - 1][words[i - 1].length() - 1])) {
                prefix[i] += 1;
            }
        }
        for (int i = 0; i < queries.size(); ++i) {
            ans[i] = (prefix[queries[i][1] + 1] - prefix[queries[i][0]]);
        }
        return ans;
    }
#else
    // 199ms
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        map<int, bool> map_words;
        vector<int> ans(queries.size());
        vector<int> prefix(words.size() + 1, 0);
        for (int i = 0; i < words.size(); ++i) {
            bool isVowel = false;
            if (checkVowel(words[i][0]) && checkVowel(words[i][words[i].length() - 1])) {
                isVowel = true;
            }
            map_words[i] = isVowel;
        }
        for (int i = 1; i <= words.size(); ++i) {
            prefix[i] = prefix[i - 1] + (map_words[i - 1] ? 1 : 0);
        }
        for (int i = 0; i < queries.size(); ++i) {
            ans[i] = (prefix[queries[i][1] + 1] - prefix[queries[i][0]]);
        }
        return ans;
    }
#endif  // OPTIMAL
};
