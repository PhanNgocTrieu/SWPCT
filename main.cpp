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
    int n;
    cin>>n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin>>a[i];
    }
    int ans = 0;
    for (int i = 1; i < n; ++i)
    {
        if (a[i] < a[i - 1])
        {
            ans = max(ans, int(1 + log2(a[i - 1] - a[i])));
            a[i] = a[i - 1];
        }
    }
    cout << ans << endl;
}

int main() {
    // setIO("lifeguards");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}