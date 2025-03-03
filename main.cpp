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

void solve() {
    ll ans = 0;

    
    cout << ans << '\n';
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