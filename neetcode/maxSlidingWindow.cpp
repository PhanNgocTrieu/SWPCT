#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (nums.size() < k) {
            return vector<int>{};
        }

        vector<int> res;
        int left = 0;
        int right = k;
        while (right <= nums.size()) {
            int curMax = nums[left];
            for (int i = left + 1; i < right; ++i) {
                if (curMax < nums[i]) {
                    curMax = nums[i];
                }
            }
            res.push_back(curMax);
            right++;
            left++;
        }
        return res;
    }
};

int main() {
    // vector<int> nums = {1,2,1,0,4,2,6};
    vector<int> nums = {1,-1};
    auto getVt = Solution{}.maxSlidingWindow(nums, 1);
    for (auto v : getVt) {
        cout << v << " ";
    }
    cout << endl;
}