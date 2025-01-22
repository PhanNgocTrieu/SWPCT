#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, x, y;
    cin >> n >> x >> y;
    long long ans = 0;
    vector<long long> elements(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> elements[i];
        sum += elements[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <n; ++j) {

        }
    }

    sort(elements.begin(), elements.end(), greater<long long>());


    int l = 0;
    int r = n - 1;

    while (l < r) {

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