// https://vjudge.net/contest/690982#problem/E
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    ll n, t;
    cin >> n >> t;
    vector<ll> a(t, -1);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        if (a[x] != -1) {
            cout << a[x] << " " << i+1 << '\n';
            return;
        }
        a[t-x] = i + 1;
    }
    cout << "IMPOSSIBLE" << endl;
}

// #define READ_FILE
// #define ASSIGNMENT

#ifndef ASSIGNMENT
#define FILE_I "./file/traffic.in"
#define FILE_O "./file/traffic.out"
#else
#define FILE_I "traffic.in"
#define FILE_O "traffic.out"
#endif

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