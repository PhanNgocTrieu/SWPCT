/*
    Links: https://usaco.org/index.php?page=viewproblem2&cpid=715
*/

#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <vector>

using namespace std;

#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f
#define ll long long

using s = std:: string;
using vll = vector<ll>;
using vb = vector<bool>;
using mll = map<ll,ll>;
using umll = unordered_map<ll,ll>;
using pll = pair<ll,ll>;
using pls = pair<ll,s>;

#define p(x, n) pow(x, n)
#define d(x) (x)*(x)

// #define READ_FILE
// #define TESTCASE 

using vvll = vector<vector<ll>>;
using vvb = vector<vector<bool>>;

ll dr[] = {1, -1, 0, 0};
ll dc[] = {0, 0, 1, -1};
ll floodSize = 0;
ll n, m, sx, sy, dx, dy;
queue<pair<ll,ll>> pos_q;
vector<vector<char>> land(55, vector<char>(55,'0'));
vector<vector<ll>> matrix(55, vector<ll>(55,0));
queue<pair<ll, ll>> qp;
ll ans = INT_MAX;
vvb visited(55, vb(55, false));

bool isValid(int x, int y) {
    if (
        x >= 0 && x < n
        && y >= 0 && y < m
    ) {
        return true;
    }
    return false;
}

bool bfs(ll i, ll j, ll color) {
    if (i < 0 || i >= n || j < 0 || j >= m) { return false; }
    return true;
}

void dfs(ll i, ll j) {
    visited[i][j] = true;
    matrix[i][j] = 2;
    for (int a = 0; a < 4; a++) {
        ll nx = i + dr[a];
        ll ny = j + dc[a];
        if (
            isValid(nx, ny)
            && !visited[nx][ny]
            && matrix[nx][ny] == 1
        ) {
            dfs(nx,ny);
        }
    }
}

int bfs() {
    queue<pair<ll,ll>> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j]) q.push({i, j});
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
            if (matrix[i][j]) {
                sx = i;
                sy = j;
            }
        }
    }
    dfs(sx, sy);
    cout << bfs();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifdef READ_FILE
    FILE* f_in = freopen("pairup.in", "r", stdin);
    FILE* f_out = freopen("pairup.out", "w", stdout);
#endif

#ifdef TESTCASE
    ll ts;
    cin >> ts;
    while (ts--) {
        solve();
    }
#else
    solve();
#endif

#ifdef READ_FILE
    fclose(f_in);
    fclose(f_out);
#endif
    return 0;
}
