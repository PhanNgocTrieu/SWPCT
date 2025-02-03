class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int ins = 1;
        int des = 1;
        // checking increase
        int step = 1;
        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i] < nums[i + 1]) {
                step++;
            }
            else {
                ins = max(ins, step);
                step = 1;
            }
        }
        ins = max(ins, step);

        step = 1;
        for (int i = 0; i < nums.size() - 1; i++) {
            // cout << "x: " << nums[i] << " - y: " << nums[i + 1] << endl;
            if (nums[i] > nums[i + 1]) {
                step++;
            }
            else {
                des = max(des, step);
                step = 1;
            }
        }
        des = max(des, step);

        return max(ins,des);
    }
};
