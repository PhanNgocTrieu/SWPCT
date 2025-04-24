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
    ll n;
    cin >> n;
    vector<pair<ll, ll>> v(n);
    for (ll i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    sort(v.begin(), v.end(), [](pair<ll,ll> a, pair<ll,ll> b) {
        return a.second < b.second;
    });

    ll curL = 0;
    ll curR = n - 1;
    ll countL = 0, countR = 0;
    ll ans = 0;
    while (curL <= curR) {
        ans = max(ans, v[curL].second + v[curR].second);
        countL++;
        countR++;

        if (countL > v[curL].first) {
            curL++;
            countL = 0;
        }

        if (countR > v[curR].first) {
            curR--;
            countR = 0;
        }
    }

    cout << ans << '\n';
}

int main() {
    setIO("pairup");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // ll t;
    // cin >> t;
    // while (t--)
        solve();

    return 0;
}