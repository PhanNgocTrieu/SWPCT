#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> hash;
        for (auto c : t) {
            hash[c]++;
        }
        int len = s.length();
        string res = s;
        for (int i = 0; i < len; ++i) {
            auto getC = s[i];
            if (hash.find(getC) != hash.end()){
                cout << "handle: " << getC << endl;
                int left = i;
                int _remained = t.length() - 1;
                if (_remained == 0) {
                    res = std::string(1, s[left]);
                    break;
                }

                auto hashtable = hash;
                hashtable[getC]--;
                for (int right = i + 1; right < len; ++right) {
                    if (_remained < 1) {
                        string tmp = s.substr(left, right - left);
                        res = s.length() > tmp.length() ? tmp : s;
                        break;
                    }
                    auto getRC = s[right];
                    if (hashtable.find(getRC) != hashtable.end()) {
                        if (hashtable[getRC] > 0) {
                            hashtable[getRC]--;
                            _remained--;
                        }
                    }
                }
                cout << "res: " << res << endl;
            }
        }
        return res;
    }
};

int main() {
    // vector<int> nums = {1,2,1,0,4,2,6};
    vector<int> nums = {1,-1};
    auto getVt = Solution{}.minWindow("ADOBECODEBANC", "ABC");
    for (auto v : getVt) {
        cout << v;
    }
    cout << endl;
}