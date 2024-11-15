// https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/description/
class Solution {
public:
    string removeDigit(string number, char digit) {
        vector<string> ans;
        for (int i = 0; i < number.length(); ++i) {
            if (number[i] == digit) {
                string tmp = number;
                tmp.erase(i, 1);
                ans.push_back(tmp);
            }
        }
        sort(ans.begin(), ans.end());
        return ans[ans.size() - 1];
    }
};