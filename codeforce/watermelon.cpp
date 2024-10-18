// https://codeforces.com/problemset/problem/4/A
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
void solve() {
    ll n;
    cin >> n;
    if (n < 3) {
        cout << "NO" << endl;
        return;
    }
    if (n % 2 != 0) {
        cout << "NO" << endl;
    }
    else {
        if (n > 2) {
            cout << "YES" << endl;
        }
    }
}

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    solve();
    return 0;
}