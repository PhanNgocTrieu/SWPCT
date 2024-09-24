#include <bits/stdc++.h>
using namespace std;

class Solution {
    unordered_map<string, int> prefixMap;
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        // Step 1: Build the prefix map for arr1
        for (int num : arr1) {
            string strNum = to_string(num);
            string prefix = "";
            for (char ch : strNum) {
                prefix += ch;
                prefixMap[prefix]++;
            }
        }
        int maxLength = 0;
        // Step 2: Check for common prefixes in arr2
        for (int num : arr2) {
            string strNum = to_string(num);
            string prefix = "";
            for (char ch : strNum) {
                prefix += ch;
                if (prefixMap.find(prefix) != prefixMap.end()) {
                    maxLength = max(maxLength, static_cast<int>(prefix.length()));
                }
            }
        }
        return maxLength;
    }
};

int main() {
    vector<int> a = {1,10,100};
    vector<int> b = {1000};
    cout << Solution{}.longestCommonPrefix(a,b) << endl;
    return 0;
}