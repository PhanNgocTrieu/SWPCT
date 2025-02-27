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

typedef long long ll;
ll n;
queue<ll> sq;
ll start = 1;

bool checkBFS(const vector<vector<ll>>& a) {
    // debug_q(sq);
    if (sq.front() != start) {
        return false;
    }

    queue<ll> q;
    vector<bool> visited(n + 1, false);
    q.push(start);
    visited[start] = true;
    auto cur_sq = sq.front();
    sq.pop();

    while(!q.empty()) {
        auto cur_u = q.front();
        q.pop();
        set<ll> _s;
        ll _size = 0;
        for (auto x : a[cur_u]) {
            if (!visited[x]) {
                visited[x] = true;
                _size++;
                _s.insert(x);
            }
        }

        while (_size-- && !_s.empty()) {
            cur_sq = sq.front();
            if (!_s.count(cur_sq)) {
                return false;
            }
            sq.pop();
            q.push(cur_sq);
        }
    }

    return sq.empty() ? true : false;
}

void solve() {
    cin >> n;
    vector<vector<ll>> a(n + 1);
    for (int i = 0; i < n - 1; i++) {
        ll u, v; cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    // debug_vv(a);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        sq.push(x);
    }

    if (checkBFS(a)) {
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