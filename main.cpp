#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define print_set(s) for (auto x : s) cout << x << " "; cout << endl;
#define print_vec(v) for (auto x : v) cout << x << " "; cout << endl;
#define print_pair_vec(v) for (auto x : v) cout << x.first << " " << x.second << endl;
void setIO(const string& file) {
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
}

void solve() {
    ll n, m, k, d;
    cin >> n >> m >> k >> d;
    vector<vector<ll>> rivers(n + 1, vector<ll>(m + 1));
    vector<ll> s_s;
    for (ll i = 0; i < n; i++) {
        for (ll j = 1; j < m; j++) {
            cin >> rivers[i][j];
        }
    }


    for (ll i = 0; i < n; ++i) {
        multiset<ll> s;
        vector<ll> dp(m);
        ll min_val = INT_MAX;
        dp[0] = 1;
        for (ll j = 1; j < m; ++j) {
            if (s.size() >= d) {
                s.erase(s.find(rivers[i][j - d]));
            }

            dp[j] = *s.begin() + 1 + rivers[i][j];
            s.insert(rivers[i][j] + 1);
        }
    }



}

int main() {
    // setIO("circlecross");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}