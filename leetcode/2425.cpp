// https://leetcode.com/problems/bitwise-xor-of-all-pairings/description/?envType=daily-question&envId=2025-01-16
// x ^ 0 = x
// x ^ x = 0

class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        // Initialize XOR results for both arrays
        int xor1 = 0;
        int xor2 = 0;

        // Get lengths of both arrays
        int len1 = nums1.size();
        int len2 = nums2.size();

        // If nums2 length is odd, each element in nums1 appears odd times in
        // final result
        if (len2 % 2 != 0) {
            for (int num : nums1) {
                xor1 ^= num;
            }
        }

        // If nums1 length is odd, each element in nums2 appears odd times in
        // final result
        if (len1 % 2 != 0) {
            for (int num : nums2) {
                xor2 ^= num;
            }
        }

        // Return XOR of both results
        return xor1 ^ xor2;
    }
};

#ifdef MORE_SPACE
class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        // Get lengths of arrays
        int len1 = nums1.size();
        int len2 = nums2.size();

        // Map to store frequency of each number
        unordered_map<int, long> freq;

        // Add frequencies for nums1 elements
        // Each element appears len2 times in final result
        for (int num : nums1) {
            freq[num] += len2;
        }

        // Add frequencies for nums2 elements
        // Each element appears len1 times in final result
        for (int num : nums2) {
            freq[num] += len1;
        }

        // XOR numbers that appear odd number of times
        int ans = 0;
        for (auto& [num, count] : freq) {
            if (count % 2 == 1) {
                ans ^= num;
            }
        }

        return ans;
    }
};
#endif
