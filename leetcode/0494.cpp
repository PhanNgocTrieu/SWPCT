#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int n;
    int range;
    vector<vector<int>> dp;
    int F(int i, int sum, vector<int>& A, int t) {
        if (i >= n) {
            return sum == t;
        }
        if (dp[i][sum + range] != -1) {
            return dp[i][sum + range];
        }
        int takePositive = F(i + 1, sum + A[i], A, t);
        int takeNegative = F(i + 1, sum - A[i], A, t);
        auto value = dp[i][sum + range] = takePositive + takeNegative;
		cout << "dp[" << i << "][" << sum + range << "] = " << value << endl;
		return value;
    }
    int findTargetSumWays(vector<int>& A, int target) {
        n = A.size();
        int totalSum = accumulate(A.begin(), A.end(), 0);
		cout << "Total Sum: " << totalSum << endl;
        range = totalSum;
        dp.resize(n , vector<int> (2*totalSum + 1 , -1));
        return F(0, 0, A, target);
    }
};

int main() {
	vector<int> nums = {1, 1, 1, 1, 1};
	int target = 3;
	Solution obj;
	cout << obj.findTargetSumWays(nums, target) << endl;
	return 0;
}
