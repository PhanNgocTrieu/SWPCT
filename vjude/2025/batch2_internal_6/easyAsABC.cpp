#include <bits/stdc++.h>
using namespace std;

#define ll long long

void setIO(const string &name) {
    if (freopen((name + ".in").c_str(), "r", stdin) == NULL) {
        cout << "Error opening input file" << endl;
        exit(1);
    }
    if (freopen((name + ".out").c_str(), "w", stdout) == NULL) {
        cout << "Error opening output file" << endl;
        exit(1);
    }
}

ll n = 3;

ll dx[] = {0, 0, 1, -1, -1, 1, -1, 1};
ll dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};

map<string, ll> mp;

void get_smallest(const vector<vector<char>>& grid, vector<vector<bool>> vs, ll i, ll j, string s) {
    if (s.length() >= 3) {
        if (mp.find(s) == mp.end()) {
            mp[s]++;
        }
        return;
    };

    vs[i][j] = true;
    for (ll k = 0; k < 8; k++) {
        ll ni = i + dx[k];
        ll nj = j + dy[k];
        if (ni < 0 || ni >= n || nj < 0 || nj >= n || vs[ni][nj]) continue;
        string new_s = s + grid[ni][nj];
        get_smallest(grid, vs, ni, nj, new_s);
    }
}

void solve() {
    vector<vector<char>> grid(n, vector<char>(n));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            vector<vector<bool>> vs(n, vector<bool>(n, false));
            // cout << "checking " << i << " " << j << endl;
            string s = "";
            s += grid[i][j];
            get_smallest(grid, vs, i, j, s);
        }
    }

    // for (auto it = mp.begin(); it != mp.end(); it++) {
    //     cout << it->first << endl;
    // }
    cout << (mp.begin()->first) << endl;
}

int main() {
    // setIO("lifeguards");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ll t;
    // cin >> t;
    // while (t--)
        solve();

    return 0;
}