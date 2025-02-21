// https://vjudge.net/contest/690982#problem/E
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    ll n, t;
    cin >> n >> t;
    vector<ll> a(1e5, -1);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        if (a[x] != -1) {
            cout << a[x] << " " << i+1 << '\n';
            return;
        }
        a[t-x] = i + 1;
    }
    cout << "IMPOSSIBLE" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    solve();
    return 0;
}