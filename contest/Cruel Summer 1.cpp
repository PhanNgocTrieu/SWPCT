#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    ll min_a = INT_MAX;
    ll max_a = -1;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    vector<ll> off_on = {0,0,0,0,0,1,1};
    for (int i = 1; i <= 7; ++i) {
        ll annual = 0;
        // cout << "i: " << i << "\n";
        for (int j = 0; j < N; ++j) {
            ll red = A[j] % 7;
            auto get = (i + red) >= 7 ? (i + red) % 7 : (i + red);
            // cout << "\t red: " << red << ", get: " << get << " off_on[get]: " << off_on[get] << "\n";
            if ( !off_on[get] ) {
                annual++;
            }
        }
        // cout << "-> annual: " << annual << "\n";
        min_a = min(min_a, annual);
        max_a = max(max_a, annual);
        // cout << "-> min_a: " << min_a << ", max_a: " << max_a << "\n";
    }
    cout << min_a << " " << max_a << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}