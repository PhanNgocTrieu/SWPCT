#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int middle = (right + left) / 2;
            if (nums[middle] == target) {
                return middle;
            }

            if (nums[middle] < target) {
                left = middle + 1;
            }
            else {
                right = middle - 1;
            }
        }
        return -1;
    }
};

int main() {
    // vector<int> nums = {1,2,1,0,4,2,6};
    vector<int> nums = {-1, 1};
    auto getVt = Solution{}.search(nums, -1);
    cout << getVt << endl;

    return 0;
}