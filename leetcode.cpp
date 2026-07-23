//https://leetcode.com/problems/partition-array-according-to-given-pivot/?envType=daily-question&envId=2025-03-03
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {

        int n = nums.size();

        if (n < 3)
            return 0;

        vector<int> dp(n, 0);

        int answer = 0;

        for (int i = 2; i < n; i++)
        {
            if (nums[i] - nums[i - 1] ==
                nums[i - 1] - nums[i - 2])
            {
                dp[i] = dp[i - 1] + 1;
            }

            answer += dp[i];
        }

        return answer;
    }
};

int main() { 
    Solution s;
    return 0;
}