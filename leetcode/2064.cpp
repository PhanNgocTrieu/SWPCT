class Solution {
public:
    int minimizedMaximum(int n, const vector<int>& quantities) {
        int l = 1, r = 1e9;
        while (l < r) {
            int m = l + (r - l) / 2;
            long long s = 0;
            for (auto q : quantities) {
                s += (long long)ceil(static_cast<double>(q) / m);
            }

            if (s > n) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return l;
    }
};