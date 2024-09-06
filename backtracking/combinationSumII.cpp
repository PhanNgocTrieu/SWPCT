#include <bits/stdc++.h>
using namespace std;
class Solution {
    public:
        vector<vector<int>> combinationSum3(int k, int n) {
            vector<int> comb;
            vector<vector<int>> results;
            backtracking(results, comb, 1, n, k);
            return results;
        }

        void backtracking(
            vector<vector<int>>& res,
            vector<int>& comb,
            int value,
            int sum,
            int k
        ) {
            int size = comb.size();
            if (sum < 0 || sum < (k - size) * value) {
                return;
            }

            if (size == k) {
                if (sum == 0) {
                    res.push_back(comb);
                }
                return;
            }

            for (int i = value; i <= 9; i++) {
                comb.push_back(i);
                backtracking(res, comb, i + 1, sum - i, k);
                comb.pop_back();
            }
        }
};

int main() {
    Solution{}.combinationSum3(3, 5);
}