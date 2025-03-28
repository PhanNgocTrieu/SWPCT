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
    multiset<pair<ll, ll>> s;
    vector<vector<ll>> rivers(n + 1, vector<ll>(m + 1));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> rivers[i][j];
        }
    }


    for (int i = 0; i < n; ++i) {
        vector<ll> dp(m);
        for (int j = 1; j < m; ++j) {

        }
    }
}

int main() {
    setIO("circlecross");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}