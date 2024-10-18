#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
            unordered_set<char> charSet;
            int res = 0;
            int l = 0;
            for (int r = 0; r < s.size(); r++) {
                while (charSet.find(s[r]) != charSet.end()) {
                    charSet.erase(s[r]);
                    l++;
                }
                charSet.insert(s[r]);
                res = max(res,r - l  + 1);
            }
            cout << res << endl;
            return res;
        }
};

int main() {
    Solution{}.lengthOfLongestSubstring("zxyzxyz");
    Solution{}.lengthOfLongestSubstring("abcxxxx");
    return 0;
}