#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define print_set(s) for (auto x : s) cout << x << " "; cout << endl;

void setIO(const string& file) {
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
}

void solve() {
    ll pers, cows;
    cin >> pers >> cows;
    vector<ll> order(cows);
    vector<vector<ll>> reference(cows, vector<ll>(cows, 0));

    for (int i = 0; i < pers; ++i) {
        for (int i = 0; i < cows; ++i) {
            cin >> order[i];
        }

        for (int i = 0; i < cows; ++i) {
            for (int j = i + 1; j < cows; ++j) {
                reference[order[i] - 1][order[j] - 1]++;
            }
        }
    }

    // for (int i = 0; i < cows; ++i) {
    //     for (int j = 0; j < cows; ++j) {
    //         cout << reference[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    ll ans = 0;
    for (int i = 0; i < cows; ++i) {
        for (int j = 0; j < cows; ++j) {
            if (reference[i][j] > 0 && reference[j][i] > 0) {
                continue;
            }
            if (reference[i][j]) ans++;
        }
    }

    cout << ans << '\n';
}

int main() {
    setIO("gymnastics");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}