#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define print_set(s) for (auto x : s) cout << x << " "; cout << endl;

void solve() {
    int n;
    cin >> n;
    vector<pair<char, ll>> cows(n);
    set<ll> candidates;
    // cout << "Initial candidates: ";

    for (int i = 0; i < n; ++i) {
        char type;
        ll p;
        cin >> type >> p;
        cows[i] = {type, p};
        candidates.insert(p);
    }

    // print_set(candidates);

    // Add boundary candidates
    if (!candidates.empty()) {
        candidates.insert(*candidates.begin() - 1);
        candidates.insert(*candidates.rbegin() + 1);
    }

    // print_set(candidates);

    int min_lies = INT_MAX;

    // Check each candidate hiding location
    for (ll x : candidates) {
        int lies = 0;
        for (auto c : cows) {
            char type = c.first;
            ll p = c.second;
            if (type == 'L' && x > p) {
                ++lies; // Cow says Bessie is <= p, but x > p
            } else if (type == 'G' && x < p) {
                ++lies; // Cow says Bessie is >= p, but x < p
            }
        }
        min_lies = min(min_lies, lies);
    }

    cout << min_lies << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}