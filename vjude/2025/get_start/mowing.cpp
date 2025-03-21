// https://vjudge.net/contest/690982#problem/F
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define ll long long

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

vector<vector<ll>> visited(2001, vector<ll>(2001, 0));

void solve() {
    vector<pair<char, ll>> moves;
    ll n; cin >> n;
    for (int i = 0; i < n; ++i) {
        char c; ll x; cin >> c >> x;
        moves.push_back({c, x});
    }
    ll start = 1000;
    ll x = start, y = start;
    ll ans = n * n;
    ll time = 0;
    for (auto m : moves) {
        for (int i = time; i < time + m.second; ++i) {
            if (visited[x][y] != 0) {
                ans = min(ans, i - visited[x][y]);
            }
            visited[x][y] = i;
            if (m.first == 'N') {
                x--;
            } else if (m.first == 'S') {
                x++;
            } else if (m.first == 'E') {
                y++;
            } else {
                y--;
            }
        }
        time += m.second;
    }
    if (ans == n * n) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

int main()
{
    setIO("mowing");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // int t; cin >> t;
    // while (t--) {
    solve();
    // }

    return 0;
}