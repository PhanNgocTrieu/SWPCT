/*
    Links: https://usaco.org/index.php?page=viewproblem2&cpid=987
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
#define debugln cout << __FUNCTION__ << __LINE__ << endl;
#define debug(x) cout << #x << ": " << x << endl;
#define debugas(a,n) for (int i = 0; i < n; ++i) { cout << #a << "[i]: " << a[i] << " "; } cout << endl;
#define debugv(v) cout << #v << " [ "; for (int i = 0; i < (v).size(); ++i) cout << v[i] << " "; cout << "]" << endl;
#define debugm(m) cout << #m << " = [ " << endl; EACH(x, m) { cout << "(" << x.first << ", " << x.second << ")" << endl;} cout << "]" << endl;
#define debugmp(m) cout << #m << " = [ " << endl; EACH(x, m) { cout << "(" << x.first << ", {" << x.second.first << ", " << x.second.second << "})" << endl;} cout << "]" << endl;
#define debugia(a, f, s) cout << "(" << f << "," << s << "): (" << a[f] << ", " << a[s] << ")" << endl;
#define debugvp(v) cout << #v <<  " [" << endl; EACH(x, v) { cout << " (" << x.first << ", " << x.second << ") " << endl; } cout << "] " << endl;
#define debugvtp(v) cout << #v << "[ " << endl; EACH(e, v) { cout << "(" << get<0>(e) << ", " << get<1>(e) << ", " << get<2>(e) << ")" << endl; } cout << "]" << endl;
#define debugset(s) cout << #s << "[ "; EACH(e, s) { cout << e << " "; } cout << "] " << endl;

#define pb push_back
#define ppb pop_back
struct Point {
    int x, y;
};

struct pair_t {
    int first;
    int second;
};

struct cows_t {
    int s;
    int t;
    int b;
};

vector<vector<char>> grid(10, vector<char>(10));
Point B;
Point L;

int dx[4] = {1, -1, 0 ,0};
int dy[4] = {0 ,0, 1, -1};

int bfs() {
    vector<vector<int>> dist(10, vector<int>(10, -1));
    queue<Point> q;
    q.push(B);
    dist[B.x][B.y] = 0;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        
        for (int i = 0; i < 4; ++i) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];

            if (
                nx >= 0 && nx < 10
                && ny >= 0 && ny < 10
                && grid[nx][ny] != 'R'
                && dist[nx][ny] == -1
            ) {
                dist[nx][ny] = dist[p.x][p.y] + 1;
                q.push({nx, ny});
            }
        }
    }
    return dist[L.x][L.y] - 1;
}


#define TESTCASE 
// #define READ_FILE
void process() {
    string s;
    cin >> s;
    auto sz = s.length();
    if (sz > 10) {
        cout << s[0] << sz - 2 << s[sz -1] << endl;
    }
    else {
        cout << s << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifdef READ_FILE
    FILE* f_in = freopen("input.in", "r", stdin);
    FILE* f_out = freopen("output.out", "w", stdout);
#endif

#ifdef TESTCASE
    ll ts;
    cin >> ts;
    while (ts--) {
        process();
    }
#else
    process();
#endif

#ifdef READ_FILE
    fclose(f_in);
    fclose(f_out);
#endif
    return 0;
}
