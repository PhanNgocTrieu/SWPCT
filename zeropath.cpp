#include <bits/stdc++.h>
using namespace std;


#define ll long long

void setIO(const string &name) {
    if (freopen((name + ".in").c_str(), "r", stdin) == NULL) {
        cout << "Error opening input file" << endl;
        exit(1);
    }
    if (freopen((name + ".out").c_str(), "w", stdout) == NULL) {
        cout << "Error opening output file" << endl;
        exit(1);
    }
}

ll dx[2] = {1, 0};
ll dy[2] = {0, 1};

struct data {
    pair<ll,ll> pos;
    ll dist;
};


ll m, n;

bool bfs(const vector<vector<ll>>& a, ll x, ll y) {
    // vector<vector<bool>> visited(a.size(), vector<bool>(a[0].size(), false));
    queue<data> q;
    data d;
    d.pos.first = x;
    d.pos.second = y;
    d.dist = a[x][y];
    q.push(d);
    // visited[x][y] = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        // cout << "v.pos: " << v.pos.first << " " << v.pos.second << endl;
        for (ll i = 0; i < 2; ++i) {
            ll new_x = v.pos.first + dx[i];
            ll new_y = v.pos.second + dy[i];
            // cout << "\tnew_x: " << new_x << " new_y: " << new_y << endl;
            if (
                new_x >= 0
                && new_x < a.size()
                && new_y >= 0
                && new_y < a[0].size()
                // && !visited[new_x][new_y]
            ) {
                ll new_dist = v.dist + a[new_x][new_y];
                if (new_x == m - 1
                && new_y == n - 1
                && new_dist == 0) {
                    return true;
                }
                // visited[new_x][new_y] = true;

                q.push({{new_x, new_y}, new_dist});
            }
        }
    }
    return false;
}

bool df(const vector<vector<ll>>& a, ll x, ll y, ll s) {
    // cout << "x: " << x << " y: " << y << endl;
    if (x < 0 || x >= m || y < 0 || y >= n) {
        return false;
    }

    if (x == m - 1 && y == n - 1) {
        if (a[x][y] + s == 0) {
            return true;
        }
        return false;
    }




    return false;
}


void solve() {
    cin >> m >> n;
    vector<vector<ll>> a(m, vector<ll>(n));
    for (auto i = 0; i < m; i++) {
        for (auto j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    if (bfs(a, 0, 0)) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }
}

int main() {
    // setIO("lifeguards");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}