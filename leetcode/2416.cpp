#include <bits/stdc++.h>
using namespace std;

// Reference: https://www.geeksforgeeks.org/trie-insert-and-search/ 

// In base of Trie, we need to add score variable to hold the number
struct Trie {
    Trie* child[26];
    int scores;
    bool wordEnds = false;

    Trie() {
        // initialize
        scores = 0;
        memset(child, 0, sizeof(child));
    }

    void add(string& s) {
        auto current = this;
        for (auto c : s) {
            // If not exist -> create new trie
            if (current->child[c - 'a'] == nullptr) {
                current->child[c - 'a'] = new Trie();
            }
            current->scores++;
            current = child[c - 'a'];
        }
        wordEnds = true;
    }

    int search(string s, int pos) {
        // if position of character in s is end of string -> return score of that character
        if (pos == s.size()) {
            return scores;
        }
        // if less than s.length() -> remain letter -> search deep inside
        return scores + child[s[pos] - 'a']->search(s, pos + 1);
    }

    void print() {
        if (this == nullptr) {
            return;
        }
        auto current = this;
        for (int i = 0; i < 26; i++) {
            
        }
    }
};


class Solution {
public:
    Solution() {
        ios::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
    }
    vector<int> sumPrefixScores(vector<string>& words) {
        vector<int> res;
        Trie* root = new Trie();
        // for (auto& s : words) root->add(s, 0);
        for (auto& s : words) root->add(s);
        for (auto& s : words) res.push_back(root->search(s, 0));
        for (auto r : res) {
            cout << r << " ";
        }
        cout << endl;
        return res;
    }
};

int main() {
    vector<string> words = {"abc","ab","bc","b"};
    Solution{}.sumPrefixScores(
        words
    );
    return 0;
}