class Solution {
public:
    vector<vector<string>> groupAnagrams(const vector<string>& strs) {
        unordered_map<string, vector<string>> mapping;
        for (auto s : strs) {
            auto tmp = s;
            sort(s.begin(), s.end());
            mapping[s].push_back(tmp);
        }
        vector<vector<string>> res;
        for (auto m : mapping) {
            res.push_back(m.second);
        }
        return res;
    }
};
