#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isValid(string s) {
        if (s == "") return true;
        cout << __FUNCTION__ << ": " << __LINE__ << endl;
        unordered_map<char, char> mapping = {
            {'(', ')'},
            {'{', '}'},
            {'[', ']'}
        };
        cout << __FUNCTION__ << ": " << __LINE__ << endl;
        stack<char> st;
        cout << __FUNCTION__ << ": " << __LINE__ << endl;
        for (auto c : s) {
            cout << __FUNCTION__ << ": " << __LINE__ << endl;
            cout << "c : " << c << endl;
            if (c == ')' 
            || c == '}' 
            || c == ']') {
                if (!st.size()) {
                    return false;
                }
                auto getTop = st.top();
                cout << "pop " << c << endl;
                if (mapping[getTop] != c) {
                    return false;
                }
                st.pop();
            }
            else {
                cout << "push: " << c << endl;
                st.push(c);
            }
        }

        if (st.empty()) {
            return true;
        }
        return false;
    }
};



int main() {
    cout << Solution{}.isValid("]]") << endl;
    return 0;
}