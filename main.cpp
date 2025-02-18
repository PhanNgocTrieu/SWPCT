// https://vjudge.net/contest/691170#problem/A
#include <bits/stdc++.h>

using namespace std;

#define ll long long

void solve() {
    ll m,n,k;
    cin >> m >> n >> k;
    ll idx = 0;
    vector<vector<string>> grid;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        vector<string> row(n * k);
        for (int j = 0; j < s.length(); ++j) {
            for (int x = j * k; x < (j * k + k); x++) {
                row[x] = s[j];
            }
        }
        for (auto z = 0; z < k; z++) {
            grid.push_back(row);
        }
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

#define READ_FILE
#define FILE_I "cowsignal.in"
#define FILE_O "cowsignal.out"

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#ifdef READ_FILE
    auto f_i = freopen(FILE_I, "r", stdin);
    auto f_o = freopen(FILE_O, "w", stdout);
#endif

    // int t; cin >> t;
    // while (t--) {
        solve();
    // }

#ifdef READ_FILE
    fclose(f_i);
    fclose(f_o);
#endif
    return 0;
}