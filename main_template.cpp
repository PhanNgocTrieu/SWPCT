#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

typedef long long ll;

unordered_map<string, ll> memo;

string arrayToString(const vector<ll>& a) {
    string s;
    for (ll num : a) {
        s += to_string(num) + ",";
    }
    return s;
}

ll maxCoins(vector<ll>& a) {
    if (a.empty()) return 0;
    string key = arrayToString(a);
    // If calculated before, return the value
    if (memo.find(key) != memo.end()) return memo[key];

    ll max_coins = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        ll coins = abs(a[i]);
        vector<ll> new_a;
        if (a[i] < 0) {
            new_a.assign(a.begin(), a.begin() + i);
        } else {
            new_a.assign(a.begin() + i + 1, a.end());
        }
        max_coins = max(max_coins, coins + maxCoins(new_a));
    }
    memo[key] = max_coins;
    return max_coins;
}

void solve() {
    ll n; cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    memo.clear();
    cout << "ans: " << maxCoins(a) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}