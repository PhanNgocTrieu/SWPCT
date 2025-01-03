class Solution {
public:
    Solution() {
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
    }
    int waysToSplitArray(vector<int>& nums) {
        long long ans = 0;
        int s = nums.size();
        vector<long long> prefix(s + 1, 0);
        for (int i = 1; i <= s; ++i) {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }

        for (int i = 1; i < s; ++i) {
            if (prefix[i] >= (prefix[s] - prefix[i])) {
                ans++;
            }
        }

        return ans;
    }
};
