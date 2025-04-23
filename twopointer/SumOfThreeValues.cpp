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
    vector<pair<ll,ll>> a(n);
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ll v; cin >> v;
        a[i] = {v, i + 1};
    }

    sort(a.begin(), a.end());

    for (ll i = 0; i < n; ++i) {
        ll left = 0, right = n - 1;
        while (left != right) {
            ll remain = x - a[i].first;
            ll pairSum = a[left].first + a[right].first;
            if (left != i && right != i && pairSum == remain) {
                cout << a[left].second << " " << a[right].second << " " << a[i].second << endl;
                return;
            }
            if (pairSum < remain) {
                left++;
            } else {
                right--;
            }
        }
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