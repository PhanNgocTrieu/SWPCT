//https://codeforces.com/problemset/problem/546/A
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
void solve() {
    ll k, n, w;
    cin >> k >> n >> w;
    ll sum = 0;
    ll factor = 1;
    while (w--) {
        sum += (k) * factor++;
    }
    // cout << sum << endl;
    ll diff = sum > n ? sum - n : 0;

    cout << diff << endl;
}

int main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    solve();
    return 0;
}