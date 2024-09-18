#include <iostream>
#include <map>
#include <vector>
using namespace std;

// class Solution {
// public:
//     vector<vector<string>> groupAnagrams(const vector<string>& strs) {
//         map<string, vector<string>> hash;
//         vector<vector<string>> res;
//         for (int i = 0; i < strs.size(); ++i) {
//             string get = strs[i];
//             sort(get.begin(), get.end());
//             hash[get].push_back(strs[i]);
//         }
//         for (map<string, vector<string>>::iterator itr = hash.begin();
//         itr != hash.end(); itr++) {
//             res.push_back(itr->second);
//         }
//         return res;
//     }
// };


class Solution {
    // struct pair {
    //     int key;
    //     int nums;
    // };

    // bool cmp(const pair& a, const pair& b) {
    //     return a.nums > b.nums;
    // }
public:
    vector<int> topKFrequent(const vector<int>& nums, int k) {
        vector<int> hash(1005, 0);
        vector<int> res;
        for (auto e : nums) {
            hash[e]++;
            cout << e << ": " << hash[e] << endl;
        }
        sort(hash.begin(), hash.end(), [](int a, int b) {
            return a >= b;
        });
        cout << hash.size() << endl;
        for (int i = hash.size() - 1; i >= 0; i--) {
            // cout << i << ": " << hash[i] << endl;
            if (k <= 0) {
                break;
            }
            if (hash[i] != 0) {
                res.push_back(i);
                k--;
            }
        }
        return res;
    }
};


int main() {
    auto get = Solution{}.topKFrequent({
        1, 2, 2, 3, 3
    }, 2);

    for (auto i : get) {
        cout << i << " ";
    }
    return 0;
}