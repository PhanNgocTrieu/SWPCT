#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int s = nums.size();
        // prefix max
        vector<int> prefixMax(s);
        prefixMax[0] = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            prefixMax[i] = max(prefixMax[i - 1], nums[i]);
        }

        // prefix min
        vector<int> prefixMin(s);
        prefixMin[s - 1] = nums[s - 1];
        for (int i = s - 2; i >= 0; --i) {
            prefixMin[i] = min(prefixMin[i + 1], nums[i]);
        }

        for (int i = 0; i < nums.size(); ++i) {
            if ((prefixMax[i] - prefixMin[i]) <= k) {
                return i;
            }
        }
        return -1;
    }
};


int main() {
    Solution s;
    vector<int> nums = {5, 0, 1, 4};
    int k = 3;
    int result = s.firstStableIndex(nums, k);
    cout << "First stable index: " << result << endl;
    return 0;
}