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

// #define READ_FILE
// #define TESTCASE 

using vvll = vector<vector<ll>>;
using vvb = vector<vector<bool>>;

ll dc[] = {1, -1, 0, 0};
ll dr[] = {0, 0, 1, -1};
ll floodSize = 0;
queue<pair<ll,ll>> pos_q;

#ifdef BACKTRACKING
    using namespace std;
    #define ll long long
    ll ans = 0;
    int length = 32;
    int N, K;
    void calc(int index, int target, int cur)
    {
        if (cur > target) return;
        if (cur == target) {
            ans++;
            return;
        }
        for (int i = index; i <= std::min(length, (int)sqrt(N)+1); i++)
        {
            cur += pow(i, K);
            calc(i+1, target, cur);
            if (cur >= target) break;
            cur -= pow(i, K);
        }
    }
    int main()
    {
        ios_base::sync_with_stdio(false);
        cin.tie(0); cout.tie(0);
        
        cin >> N >> K;
        calc(1, N, 0);
        cout << ans << '\n';

        return 0;
    }
#endif

void handle(ll i, ll n, ll sum, ll target, ll& ans) {
#ifdef DYNAMIC_PROGRAMMING
    if (sum > target) {
        return;
    }
    if (value < 1) {
        if (sum == target) {
            ans++;
        }
        return;
    }
    if (sum == target) {
        ans++;
        return;
    }
    ll pVal = p(value, n);
    handle(value - 1, n , sum, target, ans);
    handle(value - 1, n , sum + pVal, target, ans);
    // pass: 5/6;
#endif

    queue<pair<ll, ll>> q;
    q.push({i, sum});
    while (!q.empty()) {
        auto idx = q.front().first;
        auto sum = q.front().second;
        q.pop();
        if (sum == target) {
            ans++;
        }
        else if (sum < target && idx > 0) {
            ll pVal = p(idx, n);
            q.push({idx - 1, sum});
            q.push({idx - 1, sum + pVal});
        }
    }
}

void solve() {
    ll x, n;
    ll ans = 0;
    cin >> x >> n;
    int s = 1;
    do {
        int curSum = p(s,n);
        if (curSum > x) {
            break;
        }
        s++;
    } while (true);
    for (int i = s - 1; i > 0; i--) {
        // if (p(i,n) == x) {
        //     ans++;
        //     continue;
        // }
        long long sum = p(i,n);
        handle(i - 1, n, sum, x, ans);
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
