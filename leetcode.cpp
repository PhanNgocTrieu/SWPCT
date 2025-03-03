//https://leetcode.com/problems/partition-array-according-to-given-pivot/?envType=daily-question&envId=2025-03-03
#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        vector<int> pivotArray(vector<int>& nums, int pivot) {
            vector<int> pre;
            vector<int> sur;
            vector<int> piv;
            bool found = false;
            for (auto n : nums) {
                if (n < pivot) {
                    pre.push_back(n);
                }
                else if (n > pivot) {
                    sur.push_back(n);
                }
                else {
                    found = true;
                    piv.push_back(n);
                }
            }

            if (found) {
                for (auto p : piv) {
                    pre.push_back(p);
                }
                for (auto s : sur) {
                    pre.push_back(s);
                }
            }
            return pre;
        }
};



int main() { 

}