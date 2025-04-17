#include <bits/stdc++.h>
using namespace std;

#define ll long long

void setIO(const string &name) {
    if (freopen((name + ".in").c_str(), "r", stdin) == NULL) {
        cout << "Error opening input file" << endl;
        exit(1);
    }
    if (freopen((name + ".out").c_str(), "w", stdout) == NULL) {
        cout << "Error opening output file" << endl;
        exit(1);
    }
}

ll counts = INT_MAX;
bool found = false;

void checking(ll n, ll m, ll count, bool isRed = false) {
    if (n == m) {
        // cout << "n " << n << " m " << m << endl;
        // cout << "count: " << count << endl;
        counts = min(counts, count);
        found = true;
        return;
    }

    if (found || count >= 1e4) {
        return;
    }

    if (isRed) {
        if (n > m) {
            // cout << "[break n > m]: n " << n << " m " << m << endl;
            return;
        }
    }

    checking(n * 2, m, count + 1, true);
    checking(n - 1, m, count + 1);
}

void solve() {
    ll n, m;
    cin >> n >> m;
    checking(n, m, 0);
    // while (n != m) {
    //     bool isRed = abs((n * 2) - m) < abs((n - 1) - m);
    //     if (n < m) {
    //         if (isRed) {
    //             n *= 2;
    //         }
    //         else {
    //             n -= 1;
    //         }
    //     }
    //     else {
    //         n -= 1;
    //     }
    //     counts++;
    //     cout << "n: " << n << endl;
    // }
    cout << counts << endl;
}

int main() {
    // setIO("lifeguards");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ll t;
    // cin >> t;
    // while (t--)
        solve();

    return 0;
}