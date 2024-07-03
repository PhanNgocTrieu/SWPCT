#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <vector>
using namespace std;

#define make_abs(a) if (a < 0) a *= -1;
#define loop(i, s) for (ll i = 0; i < s; ++i)
#define loop_se(i, st, en) for (ll i = st; i <= en; ++i)
#define ll long long
#define print_vt(vt) \
    for (auto e : vt) { \
        cout << e << " ";   \
    }   \
    cout << endl; \

void start() {
#define READ_FILE
#ifdef READ_FILE
    FILE* f_in = freopen("input.in", "r", stdin);
    FILE* f_out = freopen("output.out", "w", stdout);
#endif

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        string s;
        cin >> n >> s;

        ll ans = 0;
        vector<ll> pref_map(n + 1, 0);
        map<ll,ll> pref_mmap;
        pref_mmap[0]++;
        loop(i, n) {
            auto getVal = static_cast<int>(s[i] - '0');
            // cout << s << " - " << getVal << endl;
            auto& curMapVal = pref_map[i + 1];
            curMapVal = pref_map[i] + getVal;
            auto idx = (i + 1) - curMapVal;
            if ( idx < 0 ) idx *= -1;
            // cout << "idx: " << idx << endl;
            if (pref_mmap[idx]) {
                ans+= pref_mmap[idx];
            }

            pref_mmap[idx]++;
        }

        cout << ans << endl;
    }


#ifdef READ_FILE
    fclose(f_in);
    fclose(f_out);
#endif
}

int main() {
    start();
    return 0;
}
