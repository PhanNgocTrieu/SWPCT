//https://leetcode.com/problems/partition-array-according-to-given-pivot/?envType=daily-question&envId=2025-03-03
#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:

    bool canSplit(vector<int>& nums, int k, int limit) {
        long long sum = 0;
        int group = 1;

        for (auto x : nums) {
            if (sum + x <= limit) {
                sum += x;
            } else {
                group++;
                sum = x;
            }
        }

        return group <= k;
    }

    int splitArray(vector<int>& nums, int k)
    {
        long long left = *max_element(nums.begin(), nums.end());
        long long right = 0;

        for (int x : nums)
            right += x;

        while (left < right)
        {
            long long mid = left + (right - left) / 2;

            if (canSplit(nums, k, mid))
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};



int main() { 
    Solution s;
    return 0;
}