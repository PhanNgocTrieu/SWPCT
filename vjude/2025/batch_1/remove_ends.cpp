// https://vjudge.net/contest/695101#problem/B
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

void solve() {
    ll n; cin >> n;
    ll ans = 0;
    vector<ll> a(n);
    vector<ll> pre(n), sur(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    pre[0] = (a[0] > 0) ? a[0] : 0;
    for (ll i = 1; i < n; i++) {
        if (a[i] > 0) {
            pre[i] = pre[i - 1] + a[i];
        }
        else {
            pre[i] = pre[i - 1];
        }
    }

    sur[n-1] = (a[n-1] < 0) ? -a[n-1] : 0;
    for (ll i = n - 2; i >= 0; --i) {
        if (a[i] < 0) {
            sur[i] = sur[i + 1] - a[i];
        }
        else {
            sur[i] = sur[i + 1];
        }
    }

    for (ll i = 0; i < n; ++i) {
        ans = max(ans, pre[i] + sur[i]);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}