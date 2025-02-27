// https://vjudge.net/contest/695101#problem/B
#include <bits/stdc++.h>
using namespace std;

#define debug_q(q) \
    { \
        cout << #q << ": "; \
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
        cout << #vv << ":\n"; \
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

#define debug_msg(m) \
    { \
        cout << m << '\n'; \
    }

typedef long long ll;

vector<ll> v;
map<ll,ll> vis;
map<ll, vector<ll>> a;

bool checkBFS() {
    ll n = v.size();
    queue<set<ll>> q;
    set<ll> s;
    s.insert(1);
    q.push(s);
    ll i = 0;

    while(!q.empty() && i < n) {
        debug_x(v[i]);
        if (vis.count(v[i])) {
            // debug_msg("vis.count(v[i])");
            return false;
        }
        vis[v[i]] = 1;
        if (q.front().size() == 0) q.pop();
        if (q.front().find(v[i]) == q.front().end()) {
            // debug_msg("q.front().find(v[i]) == q.front().end()");
            return false;
        }

        s.clear();

        for (auto x : a[v[i]]) {
            debug_x(x);
            if (vis.count(x)) {continue;}
            s.insert(x);
        }

        if (s.size() > 0) {
            set<ll> tmp = s;
            q.push(tmp);
        }
        s.clear();

        q.front().erase(v[i]);
        i++;
    }

    return true;
}

void solve() {
    ll n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        ll u, v; cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
        // if (i == 0) {
        //     start = u;
        // }
    }
    // debug_vv(a);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        // sq.push(x);
        v.push_back(x);
    }

    if (checkBFS()) {
        cout << "YES" << '\n';
    }
    else {
        cout << "NO" << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // ll t; cin >> t;
    // while (t--) {
        solve();
    // }
    return 0;
}