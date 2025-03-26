//https://vjudge.net/contest/700173#problem/A
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

void solve() {
    ll n,m;
    cin >> n >> m;
    set<ll> s;
    ll arr[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> arr[i][j];
            s.insert(arr[i][j]);
        }
    }

    map<ll,ll> mm;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (arr[i][j] == arr[i][j-1]) {
                mm[arr[i][j]]++;
            }
        }
    }

    for (int i = 0; i < m; ++i){
        for (int j = 1; j < n; ++j) {
            if (arr[j][i] == arr[j-1][i]) {
                mm[arr[j][i]]++;
            }
        }
    }

    if (m == 1 && n == 1) {
        cout << "0\n";
    }
    else if (mm.empty()){
        cout << s.size() - 1 << endl;
    }
    else {
        cout << (s.size() - mm.size()) + (mm.size() - 1) * 2 << endl;
    }
}

int main() {
    // setIO("mowing");
    ll t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

