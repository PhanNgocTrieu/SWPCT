// https://vjudge.net/contest/690982#problem/D
#include <bits/stdc++.h>

using namespace std;

#define ll long long

void solve() {
    ll N; cin >> N;
    vector<ll> pos(N);
    vector<ll> ids(N);
    vector<ll> ans(N);
    unordered_map <ll, ll> prev_mp;
    for (ll i = 0; i < N; i++) {
        cin >> pos[i];
        prev_mp.insert({pos[i], i + 1});
    }

    for (ll i = 0; i < N; i++) {
        cin >> ids[i];
    }

    for (int idx = 0; idx < N; ++idx) {
        ll k = 3;
        ll cur_pos = idx + 1;
        while (k--) {
            cur_pos = prev_mp[cur_pos];
        }
        ans[cur_pos - 1] = ids[idx];
        // cout << "pos of: " << ids[idx] << " is: " << cur_pos << " insert value: -> " << ans[cur_pos-1] << endl;
    }

    for (ll i = 0; i < N; i++) {
        cout << ans[i] << endl;
    }
}

#define READ_FILE
#define ASSIGNMENT

#ifndef ASSIGNMENT
#define FILE_I "./file/shuffle.in"
#define FILE_O "./file/shuffle.out"
#else
#define FILE_I "shuffle.in"
#define FILE_O "shuffle.out"
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