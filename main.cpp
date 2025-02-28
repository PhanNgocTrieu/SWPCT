// https://vjudge.net/contest/695101#problem/B
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

#define debug_map(m) \
    { \
        for (auto it = m.begin(); it != m.end(); it++) { \
            cout << it->first << ": " << it->second << '\n'; \
        } \
    }

typedef long long ll;

ll number_chars(string s) {
    ll n = 0;
    map<ll, bool> m;
    for (int i = 0; i < s.length(); ++i) {
        if (m[s[i]] == false) {
            m[s[i]] = true;
            n++;
            if (n >= 26) {
                break;
            }
        }
    }
    return n;
}

void solve() {
    ll n;
    ll v_max = -1;
    string s;
    cin >> n >> s;
    map<char, bool> m;
    // brute force
    for (int i = 0; i < s.length(); ++i) {
        if (m.find(s[i]) != m.end()) {
            auto left_s = string({s.begin(), s.begin() + i});
            auto right_s = string({s.begin() + i, s.end()});
            ll get_left = number_chars(left_s);
            ll get_right = number_chars(right_s);
            v_max = max(v_max, get_left + get_right);
        }
        m[s[i]] = true;
    }

    cout << v_max << '\n';

}

// #define READ_FILE
#define FILE_I "div7.in"
#define FILE_O "div7.out"

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#ifdef READ_FILE
    auto f_i = freopen(FILE_I, "r", stdin);
    auto f_o = freopen(FILE_O, "w", stdout);
#endif
    int t; cin >> t;
    while (t--) {
        solve();
    }

#ifdef READ_FILE
    fclose(f_i);
    fclose(f_o);
#endif
    return 0;
}