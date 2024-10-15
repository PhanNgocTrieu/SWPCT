// https://leetcode.com/problems/maximal-score-after-applying-k-operations/description/?envType=daily-question&envId=2024-10-14


class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
        long long res = 0;
        priority_queue<int> pq;
        for (auto n : nums) {
            pq.push(n);
        }

        for (int i = 0; i < k; ++i) {
            auto get = pq.top();
            pq.pop();
            res += get;
            get = ceil((double)get/3);
            pq.push(get);
        }

        return res;
    }
};