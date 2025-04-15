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


void solve() {
    ll n,x,y;
    vector<ll> a(n);
    cin >> n >> x >> y;

    for (auto i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto sum = accumulate(a.begin(), a.end(), 0LL);
    ll ans = 0;
    cout << "range: " << x << " " << y << endl;
    cout << "sum: " << sum << endl;
    for (auto i = 0; i < n; i++) {
        cout << "i: " << i << " a[i]: " << a[i] << endl;
        for (auto j = i + 1; j < n; ++j) {
            cout << "\tj: " << j << " a[j]: " << a[j] << endl;
            if ((sum - (a[i] + a[j])) >= x
            && (sum - (a[i] + a[j])) <= y
            ) {
                cout << "\t\tFound: " << a[i] << " " << a[j] << endl;
                ans++;
            }
        }
    }
    // sort(a.begin(), a.end());
    // auto sum = accumulate(a.begin(), a.end(), 0LL);

    cout << ans << '\n';
}

int main() {
    setIO("lifeguards");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    try {
        ll t;
        cin >> t;
        while (t--)
            solve();

    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}