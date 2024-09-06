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
using vpll = vector<pair<ll,ll>>;

// loop templates
#define F_OR(i, a, b, s) for (ll i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e , 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define EACH(x, a) for (auto& x : a)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)

#define loop_1(s) for (ll i = 0; i < s; ++i)
#define loop_se(st, en) for (ll i = st; i <= en; ++i)

#define loop(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)

#define p_m(m) \
    for (auto v : m) \
        cout << "(" << v.first << ", " << v.second  << ")" << endl;

// debug templates
#define debugmsg(m) cout << m << endl;
#define debugln cout << __FUNCTION__ << " : " << __LINE__ << endl;
#define debug(x) cout << #x << ": " << x << endl;
#define debugas(a,n) for (int i = 0; i < n; ++i) { cout << #a << "[" << i "]: " << a[i] << " "; } cout << endl;
#define debugv(v) cout << #v << " [ "; for (int i = 0; i < (v).size(); ++i) cout << v[i] << " "; cout << "]" << endl;
#define debugm(m) cout << #m << " = [ " << endl; EACH(x, m) { cout << "(" << x.first << ", " << x.second << ")" << endl;} cout << "]" << endl;
#define debugmp(m) cout << #m << " = [ " << endl; \
    EACH(x, m) { cout << "(" << x.first << ", {" << x.second.first << ", " << x.second.second << "})" << endl;} cout << "]" << endl;
#define debugia(a, f, s) cout << "(" << f << "," << s << "): (" << a[f] << ", " << a[s] << ")" << endl;
#define debugvp(v) cout << #v <<  " [" << endl; EACH(x, v) { cout << " (" << x.first << ", " << x.second << ") " << endl; } cout << "] " << endl;
#define debugvtp(v) cout << #v << "[ " << endl; EACH(e, v) { cout << "(" << get<0>(e) << ", " << get<1>(e) << ", " << get<2>(e) << ")" << endl; } cout << "]" << endl;
#define debugset(s) cout << #s << "[ "; EACH(e, s) { cout << e << " "; } cout << "] " << endl;
#define debugvvs(vvs) \
    cout<< #vvs << " [ " << endl;  \
    EACH(vs, vvs) {     \
        cout << "\t\t("; \
        EACH(s, vs)  { \
            cout << s << ", "; \
        }   \
        cout << ")" << endl;    \
    }   \
    cout << "]" << endl;

#define p(x, n) pow(x, n)
#define d(x) (x)*(x)

// #define READ_FILE
// #define TESTCASE 

using vvll = vector<vector<ll>>;
using vvb = vector<vector<bool>>;

ll dc[] = {1, -1, 0, 0};
ll dr[] = {0, 0, 1, -1};
ll floodSize = 0;
ll n, sx, sy, dx, dy;
queue<pair<ll,ll>> pos_q;
vector<vector<char>> land(55, vector<char>(55,'0'));
queue<pair<int, int>> qp;
ll ans = INT_MAX;

bool isValid(int i, int j) {
    if (i >= 0 && i < n 
    &&  j >= 0 && j < n) 
    {
        return true;
    }
    return false;
}

void bfs(int i, int j, bool& found) {
    vector<vector<bool>> vs(n, vector<bool>(n,false));
    queue<pair<int, int>> q;
    q.push({i,j});
    vs[i][j] = true;
    while(!q.empty()) {
        auto x = q.front().first;
        auto y = q.front().second;
        q.pop();
        for (int k = 0; k < 4; ++k) {
            int nx = x + dr[k];
            int ny = y + dc[k];
            if (
                isValid(nx, ny) 
                && land[nx][ny] != '0'
                && land[nx][ny] != '3'
                && !vs[nx][ny]
            ) {
                q.push({nx, ny});
                vs[nx][ny] = true;
                if (land[nx][ny] == '2') {
                    ll curVal = d((i + 1) - (nx + 1)) + d((j + 1) - (ny + 1));
                    ans = min(ans, curVal);
                    found = true;
                }
            }
        }
    }
}

void bfsMarking(int i, int j, char val, bool isGet = false) {
    queue<pair<int, int>> q;
    q.push({i,j});
    land[i][j] = val;
    if (isGet) {
        qp.push({i,j});
    }
    while(!q.empty()) {
        auto x = q.front().first;
        auto y = q.front().second;
        q.pop();
        for (int k = 0; k < 4; ++k) {
            int nx = x + dr[k];
            int ny = y + dc[k];
            if (
                isValid(nx, ny)
                && land[nx][ny] == '0'
            ) {
                q.push({nx,ny});
                land[nx][ny] = val;
                if (isGet) {
                    qp.push({nx,ny});
                }
            }
        }
    }
}

void solve() {
    cin >> n >> sx >> sy >> dx >> dy;
    for (int i = 0 ; i < n; i++) {
        s val; cin >> val;
        for (int j = 0; j < n; j++) {
            land[i][j] = val[j];
        }
    }
    // marking source
    bfsMarking(sx - 1, sy - 1, '3', true);
    // marking desination;
    bfsMarking(dx - 1, dy - 1, '2');
    bool found = false;
    while (!qp.empty()) {
        auto i = qp.front().first;
        auto j = qp.front().second;
        qp.pop();
        bfs(i,j, found);
    }
    if (!found) {
        ans = d((sx) - (dx)) + d((sy) - (dy));
    }
    cout << ans << endl;
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
