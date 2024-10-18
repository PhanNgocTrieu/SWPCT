#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    // https://neetcode.io/problems/buy-and-sell-crypto
    int maxProfit(vector<int>& prices) {
        int maxC = 0;
        int left = 0; int right = 1;
        while (right < prices.size()) {
            if (prices[right] > prices[left]) {
                maxC = max(maxC, prices[right] - prices[left]);
            }
            else {
                left = right;
            }
            right++;
        }

        return maxC;
    }
};

int main() {
    // vector<int> nums = {1,2,1,0,4,2,6};
    // vector<int> nums = {1,-1};
    vector<int> prices = {10,1,5,6,7,1};
    auto getVt = Solution{}.maxProfit(prices);
    cout << getVt << endl;

    return 0;
}