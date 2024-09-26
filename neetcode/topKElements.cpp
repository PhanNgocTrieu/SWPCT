#include <bits/stdc++.h>
using namespace std;



class Solution {
public:
    struct pair_t {
        int value = 0;
        int feq = 0;
    };

    vector<int> topKFrequent(const vector<int>& nums, int k) {
        map<int, int> hash;
        for (int i = 0; i < nums.size(); ++i) {
            hash[nums[i]]++;
        }

        vector<pair_t> sortedVector;
        vector<int> res;
        for (auto h : hash) {
            pair_t t;
            t.value = h.first;
            t.feq = h.second;
            sortedVector.push_back(t);
            // cout << h.first << " - " << h.second << endl;
        }
        // cout << endl;

        sort(sortedVector.begin(), sortedVector.end(), [](const pair_t& a, const pair_t& b) {
            return a.feq > b.feq;
        });

        for (auto v : sortedVector) {
            if (k < 1) {
                break;
            }
            res.push_back(v.value);
            // cout << v.value << " - " << v.feq << endl;
            k--;
        }

        return res;
    }
};


int main() {
    Solution{}.topKFrequent(
        {1,2,3,4,5,3,2,4,1,1,3,2,4,31},
        3
    );
    return 0;
}