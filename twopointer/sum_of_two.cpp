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
    // vector<ll> a(n);
    vector<pair<ll,ll>> a(n);
    for (ll i = 0; i < n; i++) {
        ll v; cin >> v;
        a[i] = {v, i};
    }

    sort(a.begin(), a.end());

    // for (auto _a : a) {
    //     cout << _a.first << " ";
    // }
    // cout << "\n";
    ll left = 0, right = n - 1;

    while (left < right) {
        if (a[left].first + a[right].first == x) {
            cout << a[left].second + 1 << " " << a[right].second + 1 << "\n";
            return;
        }
        else if (a[left].first + a[right].first < x)
            left++;
        else
            right--;
    }

    cout << "IMPOSSIBLE\n";
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