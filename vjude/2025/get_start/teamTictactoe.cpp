// https://vjudge.net/contest/690982#problem/F
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define ll long long

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

vector<string> board(3);
bool chars[26]; // Tracks individual winners
set<pair<char, char>> team_winners; // Tracks two-cow team winners

bool checkLine(const string& line) {
    set<char> unique_chars(line.begin(), line.end());
    if (unique_chars.size() == 1) {
        // Single cow win
        char cow = *unique_chars.begin();
        if (!chars[cow - 'A']) {
            chars[cow - 'A'] = true;
            return true;
        }
    } else if (unique_chars.size() == 2) {
        // Two-cow team win
        auto it = unique_chars.begin();
        char cow1 = *it++;
        char cow2 = *it;
        if (cow1 > cow2) swap(cow1, cow2); // Ensure consistent ordering
        team_winners.insert({cow1, cow2});
    }
    return false;
}

void solve() {
    // Input the board
    for (int i = 0; i < 3; i++) {
        cin >> board[i];
    }

    // Check rows
    for (int i = 0; i < 3; i++) {
        checkLine(board[i]);
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        string col = "";
        for (int i = 0; i < 3; i++) {
            col += board[i][j];
        }
        checkLine(col);
    }

    // Check diagonals
    string diag1 = "", diag2 = "";
    for (int i = 0; i < 3; i++) {
        diag1 += board[i][i];
        diag2 += board[i][2 - i];
    }
    checkLine(diag1);
    checkLine(diag2);

    // Count results
    ll winners = count(chars, chars + 26, true);
    ll pairs = team_winners.size();

    cout << winners << "\n" << pairs;
}

int main()
{
    setIO("tttt");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int t; cin >> t;
    // while (t--) {
    solve();
    // }

    return 0;
}