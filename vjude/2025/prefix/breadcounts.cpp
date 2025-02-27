// https://vjudge.net/contest/690826#problem/A
#include <bits/stdc++.h>
using namespace std;

#define debug_q(q) \
    { \
        auto q_ = q; \
        while (!q_.empty()) { \
            cout << q_.front() << ' '; \
            q_.pop(); \
        } \
        cout << '\n'; \
    }

#define debug_v(v) \
    { \
        cout << #v << ": "; \
        for (auto x : v) { \
            cout << x << ' '; \
        } \
        cout << '\n'; \
    }

#define debug_vv(vv) \
    { \
        for (int i = 0; i < vv.size(); i++) { \
            cout << "v[" << i << "]: "; \
            for (auto x : vv[i]) { \
                cout << x << ' '; \
            } \
            cout << '\n'; \
        } \
    }

#define debug_x(x) \
    { \
        cout << #x << ": " << x << '\n'; \
    }

#define debug_msg(msg) \
    { \
        cout << #msg << '\n'; \
    }

typedef long long ll;

void solve() {
    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    vector<ll> pre_1(n + 1, 0), pre_2(n + 1, 0), pre_3(n + 1, 0);
    for (ll i = 1; i <= n; i++) {
        ll x; cin >> x;
        pre_1[i] = pre_1[i - 1] + ((x == 1) ? 1 : 0);
        pre_2[i] = pre_2[i - 1] + ((x == 2) ? 1 : 0);
        pre_3[i] = pre_3[i - 1] + ((x == 3) ? 1 : 0);
    }
    vector<pair<ll, ll>> queries(q);
    for (int i = 0; i < q; i++) {
        ll l, r; cin >> l >> r;
        cout << pre_1[r] - pre_1[l-1] << " "
            << pre_2[r] - pre_2[l-1] << " "
            << pre_3[r] - pre_3[l-1] << '\n';
    }
}

#define READ_FILE
#define ASSIGNMENT

#ifndef ASSIGNMENT
#define FILE_I "file/bcount.in"
#define FILE_O "file/bcount.out"
#else
#define FILE_I "bcount.in"
#define FILE_O "bcount.out"
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
    // Sometime could not write to file, comment this below function of fclose()
    fclose(f_o);
#endif
    return 0;
}