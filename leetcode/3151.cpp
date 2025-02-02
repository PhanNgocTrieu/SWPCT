class Solution {
public:
    bool isArraySpecial(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) { return true; }

        for (int i = 0; i < n - 1; ++i) {
            bool left = nums[i] % 2 == 0;
            bool right = nums[i + 1] % 2 == 0;
            if (
                left == right
            ) {
                return false;
            }
        }

        return true;
    }
};
