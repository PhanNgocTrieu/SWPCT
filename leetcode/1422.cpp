class Solution {
public:
    int maxScore(string s) {
        int size = s.length();
        vector<int> left(size + 1, 0);
        vector<int> right(size + 1, 0);

        int ans = 0;
        for (int i = 1; i <= s.length(); ++i) {
            left[i] = left[i - 1];
            right[i] = right[i - 1];
            if (s[i - 1] == '1') {
                right[i] += 1;
            }
            else {
                left[i] += 1;
            }
        }

        for (int i = 1; i < size; ++i) {
            ans = max(
                ans,
                (left[i] - left[0]) + (right[size] - right[i])
            );
        }

        return ans;
    }
};