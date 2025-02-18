// https://vjudge.net/contest/690982#problem/C
#include <bits/stdc++.h>

using namespace std;

#define ll long long

void solve() {
    ll s, e; cin >> s >> e;
    ll ans = 0;

    if (s == e) {
        cout << "0" << endl;
        return;
    }

    ll steps = 0;
    ll k = 0;
    ll forward = 1;
    ll prev_pos;
    ll cur_pos = s;

    if (s < e) {
        while (
            cur_pos < e
        ) {
            steps = (1 << k) * forward;
            prev_pos = cur_pos;
            cur_pos = s + steps;
            ans += abs(cur_pos - prev_pos);
            // cout << "steps: " << steps << endl;
            // cout << "prev_pos: " << prev_pos << endl;
            // cout << "cur_pos: " << cur_pos << endl;
            // cout << "ans: " << ans << endl;
            forward *= -1;
            k++;
        }

        ans -= (cur_pos - e);
    } else {
        // cout << "down: " << s << " to: " << e << endl;
        while (
            cur_pos > e
        ) {
            steps = (1 << k) * forward;
            prev_pos = cur_pos;
            cur_pos = s + steps;
            ans += abs(cur_pos - prev_pos);
            // cout << "steps: " << steps << endl;
            // cout << "prev_pos: " << prev_pos << endl;
            // cout << "cur_pos: " << cur_pos << endl;
            // cout << "ans: " << ans << endl;
            forward *= -1;
            k++;
        }

        ans -= (e - cur_pos);
    }

    cout << ans << endl;
}

#define READ_FILE
#define ASSIGNMENT

#ifndef ASSIGNMENT
#define FILE_I "./file/lostcow.in"
#define FILE_O "./file/lostcow.out"
#else
#define FILE_I "lostcow.in"
#define FILE_O "lostcow.out"
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