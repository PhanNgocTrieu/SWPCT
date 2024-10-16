#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> st;
        for (auto digit : num) {
            while (!st.empty() && k > 0 && st.top() > digit) {
                st.pop();
                k--;
            }
            st.push(digit);
        }

        // This case for hanlding the case of 1 number with k = 1
        while (k > 0 && !st.empty()) {
            st.pop();
            k--;
        }

        std::string result;
        while(!st.empty()) {
            result += st.top();
            st.pop();
        }

        std::reverse(result.begin(), result.end());

        size_t pos = result.find_first_not_of('0');
        result = (pos == std::string::npos) ? "0" : result.substr(pos);

        return result;
    }
};