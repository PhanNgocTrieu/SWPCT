#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <vector>

#define ll long long
#define make_abs(a) if (a < 0) a *= -1;
#define loop(i, s) for (ll i = 0; i < s; ++i)
#define loop_se(i, st, en) for (ll i = st; i <= en; ++i)
#define print_vt(vt) \
    for (auto e : vt) { \
        cout << e << " ";   \
    }   \
    cout << endl; \

#define p_m(m) \
    for (auto v : m) \
        cout << "(" << v.first << ", " << v.second  << ")" << endl;

using namespace std;
using s = std::string;
using vll = vector<ll>;
using mll = map<ll,ll>;
using umll = unordered_map<ll,ll>;
using pll = pair<ll,ll>;
using pls = pair<ll,s>;


#define READ_FILE
// #define TESTCASE

void solve() {
    ll N;
    s val;
    cin >> N >> val;
    // cout << "string: " << val << endl;
    ll offset = 0;
    ll ans = 0;
    vector<int> pref(N + 1,0);
    map<ll,ll> sumMap; 
    sumMap[0]++;
    loop_se(i, 1, N) {
        // cout << "val[" << i << "] - '0':" << val[i] - '0' << endl;
        auto iVal = val[i - 1] - '1';
        pref[i] = pref[i - 1] + iVal;
        ans += sumMap[pref[i]];
        sumMap[pref[i]]++;
    }

    print_vt(pref);
    p_m(sumMap);

    cout << ans << endl;
}

int main() {
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
#endif

#ifdef READ_FILE
    fclose(f_in);
    fclose(f_out);
#endif
    return 0;
}
