#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


#ifndef SLIDING_WINDOW
class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int left = 0, maxBeauty = 0;
        for (int right = 0; right < nums.size(); ++right) {
            while (nums[right] - nums[left] > 2 * k) {
                ++left;
            }
            maxBeauty = max(maxBeauty, right - left + 1);
        }
        return maxBeauty;
    }
};
#else
class Solution {
public:
    bool canAchieve(vector<int>& nums, int k, int length) {
        for (int i = 0; i + length - 1 < nums.size(); ++i) {
            if (nums[i + length - 1] - nums[i] <= 2 * k) {
                return true;
            }
        }
        return false;
    }
    int maximumBeauty(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int left = 1, right = nums.size(), maxBeauty = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(nums, k, mid)) {
                maxBeauty = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return maxBeauty;
    }
};
#endif

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Example usage
    Solution solution;
    vector<int> nums = {1, 3, 6, 9, 12};
    int k = 3;
    int result = solution.maximumBeauty(nums, k);
    cout << "Maximum Beauty: " << result << "\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Example usage
    Solution solution;
    vector<int> nums = {1, 3, 6, 9, 12};
    int k = 3;
    int result = solution.maximumBeauty(nums, k);
    cout << "Maximum Beauty: " << result << "\n";

    return 0;
}