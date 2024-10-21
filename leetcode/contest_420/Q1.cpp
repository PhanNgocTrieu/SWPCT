// https://leetcode.com/contest/weekly-contest-420/problems/find-the-sequence-of-strings-appeared-on-the-screen/description/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<string> stringSequence(string target) {
        vector<string> res;
        // for (int i = 0; i < target.length(); ++i) {
        string tmp = "";
        for (auto c : target) {
            // processing of key press
            char start = 'a';
            tmp += start;
            res.push_back(tmp);
            do {
                if (start == c) {
                    // res.push_back(tmp);
                    break;
                }
                // press second to approach the target
                start = (++start > 'z') ? 'a' : start;
                tmp[tmp.length() - 1] = start;
                res.push_back(tmp);
                cout << "char: " << start << endl;
            } while (true);


            if (tmp == target) {
                break;
            }
        }
        // }
        return res;
    }
};