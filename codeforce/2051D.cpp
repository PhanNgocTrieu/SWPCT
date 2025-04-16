#include <bits/stdc++.h>
using namespace std;

#define ll long long

void setIO(const string &name) {
    if (freopen((name + ".in").c_str(), "r", stdin) == NULL) {
        cout << "Error opening input file" << endl;
        exit(1);
    }
    if (freopen((name + ".out").c_str(), "w", stdout) == NULL) {
        cout << "Error opening output file" << endl;
        exit(1);
    }
}

ll count_lessthan(const vector<ll>& a, ll lx, ll sum) {
    ll count = 0;
    ll n = a.size();
    int j = 0;
    // If (sum - a[i] - a[j] < lx, then all elements from a[j] to a[n-1] are also less than lx
    for (int i = n - 1; i >= 0; --i) {
        while (j < n && (sum - a[i] - a[j]) >= lx) {
            j++;
        }
        count += (n - j);
    }

    // cout << "[before remove duplicated] count: " << count << endl;
    // We need to remove the pairs (a[i], a[i]) from the count
    for (int i = 0; i < n; ++i) {
        if ((sum - a[i] - a[i]) < lx) {
            count--;
        }
    }

    // cout << "[after remove duplicated] count: " << count << endl;
    // Since we counted each pair (a[i], a[j]) twice, we need to divide the count by 2
    return count / 2;
}

void solve() {
    ll n, x, y;
    cin >> n >> x >> y;
    ll sum = 0;
    vector<ll> a(n);
    for (auto i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    sort(a.begin(), a.end());

    ll lessthanY = count_lessthan(a, y + 1, sum);
    ll lessthanX = count_lessthan(a, x, sum);

    // cout << "lesserY: " << lessthanY << endl;
    // cout << "greaterX: " << lessthanX << endl;
    // cout << "sum: " << (lessthanY - lessthanX) << endl;

#ifdef TLE
    for (ll l = 0; l < n; ++l) {
        ll r = n - 1;
        while (l < r) {
            ll sum_ = sum - a[l] - a[r];
            if (sum_ > y) {
                break;
            }
            if (sum_ >= x && sum_ <= y) {
                ans++;
            }
            r--;
        }
    }
#endif
    cout << (lessthanY - lessthanX) << '\n';
}


int main() {
    setIO("lifeguards");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}



