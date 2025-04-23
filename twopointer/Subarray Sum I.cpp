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

void solve()
{
    ll n, x;
    cin >> n >> x;
    vector<ll> a(n);
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll l = 0;
    ll r = 0;
    ll s = 0;
    while (l < n && r < n) {
        while (r < n) {
            s += a[r++];
            if (s == x) {
                ans++;
            }
            else if (s > x) {
                s -= a[--r];
                break;
            }
        }
        s -= a[l++];
    }

    cout << ans << endl;
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