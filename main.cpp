#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int res = 1;
    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    vector<int> array_input;
    array_input.resize(n, 0);
    res = 2;
    int l = 0;
    int r = n - 1;
    while (l <= r) {
        auto cal = (r - l + 1) / 2;
        // cout << "cal: " << cal << endl;
        if (cal <= 2) {
            res = max(res, r - l);
        }
        r--;
    }
    cout << res << endl;
}

int main() {
    int t; cin >> t;
    while (t--) solve();
    return 0;
}