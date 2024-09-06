/*
    Links: https://cses.fi/problemset/task/1619
*/

#include <bits/stdc++.h>

using namespace std;

#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f
#define ll long long
#define SIZE 1000
#define WIDTH 1000

using s = std::string;
using vll = vector<ll>;
using vb = vector<bool>;
using mll = map<ll,ll>;
using umll = unordered_map<ll,ll>;
using pll = pair<ll,ll>;
using pls = pair<ll,s>;
using v2dll = vector<vector<ll>>;
using vpll = vector<pair<ll,ll>>;

#define v std::vector;
#define pb push_back;
#define p std::pair;

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
#define debug(x) cout << #x << ": " << x << endl;
#define debugas(a,n) for (int i = 0; i < n; ++i) { cout << #a << "[i]: " << a[i] << " "; } cout << endl;
#define debugv(v) cout << #v << "[ "; for (int i = 0; i < (v).size(); ++i) cout << v[i] << " "; cout << "]" << endl;
#define debugm(m) cout << #m << " = [ " << endl; EACH(x, m) { cout << "\t(" << x.first << ", " << x.second << ")" << endl;} cout << "]" << endl;
#define debugmp(m) cout << #m << " = [ " << endl; EACH(x, m) { cout << "(" << x.first << ", {" << x.second.first << ", " << x.second.second << "})" << endl;} cout << "]" << endl;
#define debugia(a, f, s) cout << "(" << f << "," << s << "): (" << a[f] << ", " << a[s] << ")" << endl;
#define debugln() cout << __FUNCTION__ << __LINE__ << endl;
#define debugvp(a) cout << #a << " = [ \n"; EACH(x, a) { cout << "(" << x.first << "," << x.second << ")" << endl; } cout << "]\n"; 

// #define READ_FILE
// #define TESTCASE

void solve() {
    ll ans = 0;
    ll N;  cin >> N;
    vpll customers;

    loop(N) {
        ll in, out;
        cin >> in >> out;
        // Check in person -> plus 1
        customers.push_back({in, 1});
        // Check out person -> minus 1
        customers.push_back({out, -1});
    }

    // sorting as the time of in and out
    sort(customers.begin(), customers.end());
    // debugvp(customers)

    // Holding the current people in anytime
    ll curPeo = 0;
    EACH(x, customers) {
        curPeo += x.second;
        ans = max(ans, curPeo);
    }

    cout << ans << endl;
}

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

#ifdef READ_FILE
    FILE* f_in = freopen("paintbarn.in", "r", stdin);
    FILE* f_out = freopen("paintbarn.out", "w", stdout);
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
