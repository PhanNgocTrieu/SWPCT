// https://codeforces.com/problemset/problem/1850/B
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    priority_queue<pair<int, pair<int,int>>> pq;
    for (int i = 0; i < n; i++) {
        int l, q; cin >> l >> q;
        if (l <= 10) {
            pq.push({q, {l, i + 1}});
        }
    }

    cout << pq.top().second.second << endl;
    // while (!pq.empty()) {
    //     auto p = pq.top();
    //     pq.pop();
    //     cout << p.second.second << ": " << p.first << " - " << p.second.first << endl;
    // }
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