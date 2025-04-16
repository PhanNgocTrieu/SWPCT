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

void solve() {
    ll n, x, y;
    cin >> n >> x >> y;
    vector<ll> a(n);
    for (auto i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for (auto a_ : a) {
        cout << a_ << " ";
    }
    cout << endl;
    auto sum = accumulate(a.begin(), a.end(), 0LL);
    y = sum - y;
    x = sum - x;
    ll ans = 0;
    cout << "x: " << x << ", y: " << y << endl;
    for (auto i = 0; i < n; ++i) {
        cout << "i " << i << " -> y - a[i]: " << y - a[i] << ", x - a[i]: " << x - a[i] << endl;
        auto l = distance(a.begin(), lower_bound(begin(a), end(a), y - a[i]));
        auto r = distance(a.begin(), upper_bound(begin(a), end(a), x - a[i]));
        cout << "l = " << l << ", r " << r << endl;
        ans += max(0ll, r - l);
        if ( i < r && i >= l ) ans--;
    }

    ans >>= 1;

    cout << ans << endl;
}

int main() {
    setIO("lifeguards");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}



