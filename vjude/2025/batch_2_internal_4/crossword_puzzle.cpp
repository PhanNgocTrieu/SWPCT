//https://vjudge.net/contest/700173#problem/B
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define SIZE 10

#define print_vector(v) for (auto x : v) cout << x << "\n"; cout << endl;

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

bool checkVertical(
    int x,
    int y,
    vector<string>& grid,
    string curWord)
{
    int n = curWord.length();
    for (int i = 0; i < n; ++i) {
        if (grid[x + i][y] == '-'
        || grid[x + i][y] == curWord[i]) {
            grid[x + i][y] = curWord[i];
        }else {
            return false;
        }
    }
    return true;
}

bool checkHorizontal(
    int x,
    int y,
    vector<string>& grid,
    string curWord)
{
    int n = curWord.length();
    for (int i = 0; i < n; ++i) {
        if (grid[x][y + i] == '-'
        || grid[x][y + i] == curWord[i]) {
            grid[x][y + i] = curWord[i];
        }
        else {
            return false;
        }
    }
    return true;
}


void handlePuzzle(vector<string>& words,
    vector<string> grid,
    int index,
    int n)
{
    if (index < words.size()) {
        string currentWord = words[index];
        // cout << "currentWord: " << currentWord << endl;
        int maxLen = n - currentWord.length();
        // cout << "maxLen: " << maxLen << endl;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j <= maxLen; ++j) {
                vector<string> temp = grid;
                bool flag = checkVertical(j, i, temp, currentWord);
                if (flag) {
                    // print_vector(temp);
                    handlePuzzle(words, temp, index + 1, n);
                }
            }
        }

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j <= maxLen; ++j) {
                vector<string> temp = grid;
                bool flag = checkHorizontal(i, j, temp, currentWord);
                if (flag) {
                    // print_vector(temp);
                    handlePuzzle(words, temp, index + 1, n);
                }
            }
        }
    }
    else {
        // cout << "Puzzle solved" << endl;
        for (int i = 0; i < SIZE; ++i) {
            cout << grid[i] << endl;
        }
        return;
    }
}

void solve() {
    vector<string> grid(SIZE);
    string words;
    for (int i = 0; i < SIZE; ++i) {
        cin >> grid[i];
    }
    cin >> words;
    vector<string> wordList;
    stringstream ss(words);
    string word;
    while (getline(ss, word, ';')) {
        wordList.push_back(word);
    }

    handlePuzzle(wordList, grid, 0, SIZE);

}

int main() {
    setIO("mowing");
    // ll t;
    // cin >> t;
    // while (t--) {
        solve();
    // }
    return 0;
}

