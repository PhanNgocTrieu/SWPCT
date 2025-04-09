#include <bits/stdc++.h>
using namespace std;


#define ll long long

void setIO(const string &name) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if (freopen((name + ".in").c_str(), "r", stdin) == NULL) {
        cout << "Error opening input file" << endl;
        exit(1);
    }
    if (freopen((name + ".out").c_str(), "w", stdout) == NULL) {
        cout << "Error opening output file" << endl;
        exit(1);
    }
}


void solve() {
    ll n;
    cin >> n;
    vector<pair<ll, ll>> intervals(n + 1, {0, 0});

    for (ll i = 1; i <= n; i++) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    sort(intervals.begin(), intervals.end());

    vector<ll> prefix(n + 1, 0), suffix(n + 1, 0);

    ll prev_s = 0;
    ll prev_e = 0;
    for (ll i = 1; i <= n; ++i) {
        auto inter = intervals[i];
        ll start = max(prev_s, max(inter.first, prev_e));
        ll end = max(inter.second, prev_e);
        // cout << "Calculate: " << start << " " << end << endl;
        prev_s = max(prev_s, start);
        prev_e = max(prev_e, end);
        // cout << "prev_s: " << prev_s << " prev_e: " << prev_e << endl;
        prefix[i] = prefix[i - 1] + (end - start);
    }

    // cout << "prefix: ";
    // for (auto p : prefix) {
    //     cout << p << " ";
    // }
    // cout << endl;



    prev_s = INT_MAX;
    prev_e = INT_MAX;
    for (ll i = n; i > 0; --i) {
        auto inter = intervals[i];
        ll start = inter.first;
        ll end = min(inter.second, prev_s);
        // cout << "Calculate: " << start << " " << end << endl;
        prev_s = min(prev_s, start);
        prev_e = min(prev_e, end);
        // cout << "prev_s: " << prev_s << " prev_e: " << prev_e << endl;
        suffix[i - 1] = suffix[i] + (end - start);
    }

    // cout << "surfix: ";
    // for (auto p : suffix) {
    //     cout << p << " ";
    // }
    // cout << endl;

    ll max_ = 0;
    for (int i = 0; i < n; ++i) {
        // ll i_s = (i == n) ? 0 : prefix[i - 1];
        // cout << "prefix: " << prefix[i] << " suffix: " << suffix[i + 1] << endl;
        max_ = max(max_, prefix[i] + suffix[i + 1]);
    }



    cout << max_ << '\n';

}

int main() {
    setIO("lifeguards");
    try {
        solve();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}