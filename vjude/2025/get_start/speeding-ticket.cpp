// https://vjudge.net/contest/690982#problem/B
#include <bits/stdc++.h>

using namespace std;

#define ll long long

void solve() {
    ll m, n; cin >> m >> n;
    vector<pair<ll,ll>> roads(m);
    vector<pair<ll,ll>> drives(n);
    ll prev = 0;
    for (ll i = 0; i < m; i++) {
        ll length, speed;
        cin >> length >> speed;
        roads[i] = {length + prev, speed};
        prev = length + prev;
    }
    prev = 0;
    for (ll i = 0; i < n; i++) {
        ll length, speed;
        cin >> length >> speed;
        drives[i] = {length + prev, speed};
        prev = length + prev;
    }

    ll r_idx = 0;
    ll d_idx = 0;
    ll max_over = 0;
    do {
        if (drives[d_idx].second > roads[r_idx].second) {
            max_over = max(max_over, drives[d_idx].second - roads[r_idx].second);
        }
        if (drives[d_idx].first == roads[r_idx].first) {
            d_idx++;
            r_idx++;
        } else if (drives[d_idx].first > roads[r_idx].first) {
            r_idx++;
        } else {
            d_idx++;
        }
    } while (r_idx < m && d_idx < n);

    cout << max_over << endl;
}

#define READ_FILE
#define ASSIGNMENT

#ifndef ASSIGNMENT
#define FILE_I "./file/speeding.in"
#define FILE_O "./file/speeding.out"
#else
#define FILE_I "speeding.in"
#define FILE_O "speeding.out"
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