class Solution {
public:
    string minWindow(string s, string t) {
        string ans = "";
        map<char, int> c_m;
        for (auto c : t) { 
            c_m[c]++;
        }

        int charRemains = t.length();
        int minWindow[2] = {0, INT_MAX};
        int sIdx = 0;
        for (int i = 0; i < s.length(); ++i) {
            char ch = s[i];
            if (c_m.find(ch) != c_m.end() && c_m[ch] > 0) {
                charRemains--;
            }
            c_m[ch]--;

            // When finishing finding the string for the current range, change to next range
            if (charRemains == 0) {
                while (true) {
                    char charAtStart = s[sIdx];
                    if (c_m.find(charAtStart) != c_m.end()
                    && c_m[charAtStart] == 0) {
                        break;
                    }
                    c_m[charAtStart]++;
                    sIdx++;
                }

                if (i - sIdx < minWindow[1] - minWindow[0]) {
                    minWindow[0] = sIdx;
                    minWindow[1] = i;
                }

                c_m[s[sIdx]]++;
                charRemains++;
                sIdx++;
            }
        } 
        return minWindow[1] >= s.length() ? "" : s.substr(minWindow[0], minWindow[1] - minWindow[0] + 1);
    }
};
