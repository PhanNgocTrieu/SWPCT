// https://vjudge.net/contest/695512#problem/C
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

bool cmp(pair<ll, ll> a, pair<ll, ll> b) {
    return a.first < b.first;
}

ll min_s = 1e9;
queue<pair<ll, ll>> q;
vector<vector<ll>> distance(1010, vector<ll>(1010, 1e9));
ll dx[] = {0, 0, 1, -1};
ll dy[] = {1, -1, 0, 0};
ll r,c;


void bfs(const vector<vector<char>>& v) {
    ::distance[q.front().first][q.front().second] = 0;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            ll x = p.first + dx[i];
            ll y = p.second + dy[i];
            if (
                x >= 0 && x < r &&
                y >= 0 && y < c &&
                ::distance[x][y] == 1e9 &&
                v[x][y] != 'T') {

                if (v[x][y] == 'S') {
                    min_s = ::distance[p.first][p.second] + 1;
                }

                ::distance[x][y] = ::distance[p.first][p.second] + 1;
                q.push({x, y});
            }
        }
    }
}


void solve() {
    ll ans = 0;
    cin >> r >> c;
    vector<vector<char>> v(r, vector<char>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> v[i][j];
            if (v[i][j] == 'E') {
                q.push({i, j});
            }
        }
    }
    bfs(v);

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (::distance[i][j] <= min_s &&
            v[i][j] >= '0' && v[i][j] <= '9') {
                ans += v[i][j] - '0';
            }
        }
    }

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