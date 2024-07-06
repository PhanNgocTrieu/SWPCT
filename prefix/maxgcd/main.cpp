/*
    Links: https://atcoder.jp/contests/abc125/tasks/abc125_c
*/

#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <vector>

using namespace std;

#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f
#define ll long long

using s = std::string;
using vll = vector<ll>;
using mll = map<ll,ll>;
using umll = unordered_map<ll,ll>;
using pll = pair<ll,ll>;
using pls = pair<ll,s>;


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
#define loop_se(i, st, en) for (ll i = st; i <= en; ++i)

#define loop(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)

#define p_m(m) \
    for (auto v : m) \
        cout << "(" << v.first << ", " << v.second  << ")" << endl;

// debug templates
#define debug(x) cerr << #x << ": " << x << endl;
#define debugas(a,n) for (int i = 0; i < n; ++i) { cerr << #a << "[i]: " << a[i] << " "; } cout << endl;
#define debugv(v) cerr << #v << "[ "; for (int i = 0; i < (v).size(); ++i) cerr << v[i] << " "; cerr << "]" << endl;


// #define READ_FILE
// #define TESTCASE

/*
    gcd(7,8,6)
    -> f[] = 7 1 2
    -> b[] = 2 2 6
    --------------
        0: l = inf, r = 2
        1: l = 7, 2 = 2
        2: l = 1, 2 = inf

        gcd = 2
 */

void solve() {
    ll N;
    cin >> N;
    ll a[N];
    ll ans = 0;
    ll f[N], b[N];
    loop(N) { 
        cin >> a[i]; 
    }
    f[0] = a[0];
    loop_se(i, 1, N) {
        f[i] = __gcd(a[i], f[i - 1]);
    }
    b[N-1] = a[N-1];
    for (int i = N - 2; i >= 0; --i) {
        b[i] = __gcd(a[i], b[i + 1]);
    }

    loop(N) {
        ll ans_;
        int l = i - 1, r = i + 1, gcd_l, gcd_r;
        if (l < 0) {
            gcd_l = inf;
            gcd_r = b[r];
        } else if (r >= N) {
            gcd_r = inf;
            gcd_l = f[l];
        } else {
            gcd_l = f[l];
            gcd_r = b[r];
        }

        if (gcd_l == inf) ans_ = gcd_r;
        else if (gcd_r == inf) { ans_ = gcd_l; }
        else ans_ = __gcd(gcd_l, gcd_r);

        ans = max(ans, ans_);
    }

    cout << ans << endl;
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
        solve();
    }
#else
    solve();
    // cout << __gcd(7, 6) << endl;
#endif

#ifdef READ_FILE
    fclose(f_in);
    fclose(f_out);
#endif
    return 0;
}
