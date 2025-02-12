// https://codeforces.com/contest/2059/problem/A
#include <bits/stdc++.h>
using namespace std;

int a[55], b[55];

void solve() {
    set<int> ma, mb;
    int n; cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ma.insert(a[i]);
    }

    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        mb.insert(b[i]);
    }

    if (ma.size() + mb.size() < 4) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}