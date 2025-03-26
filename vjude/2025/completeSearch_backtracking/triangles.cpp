#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define print_set(s) for (auto x : s) cout << x << " "; cout << endl;

void setIO(const string& file) {
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> x(n);
    vector<ll> y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        cout << "(x,y): " << "(" << x[i] << "," << y[i] << ") " << endl;
        for (int j = 0; j < n; ++j) {
            cout << "\t(x,y): " << "(" << x[j] << "," << y[j] << ") " << endl;
            for (int k = 0; k < n; ++k) {
                cout << "\t\tk(x,y): " << "(" << x[k] << "," << y[k] << ") " << endl;
                if (y[i] == y[j] && x[i] == x[k]) {
                    ans = max(ans, abs(x[j] - x[i]) * abs(y[k] - y[i]));
                    cout << "\t\t\t->max: " << ans << endl;
                }
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    setIO("triangles");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}