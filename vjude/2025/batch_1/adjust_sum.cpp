// https://vjudge.net/contest/690982#problem/E
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    ll x,y;
    cin >> x >> y;

    if (y == x + 1) {
        cout << "YES" << endl;
    }
    else if (x > y && (x - y + 1) % 9 == 0) {
        cout << "YES" << endl;
    }
    else cout << "NO" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    ll t; cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}