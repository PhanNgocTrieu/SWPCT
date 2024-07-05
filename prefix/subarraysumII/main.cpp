/*
    links: https://cses.fi/problemset/task/1661
*/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define loop(i, s) for (ll i = 0; i < s; ++i)
#define loop_se(i, st, en) for (ll i = st; i <= en; ++i)
#define ll long long
#define print_vt(vt) \
    for (auto e : vt) { \
        cout << e << " ";   \
    }   \
    cout << endl; \

void start() {
    // FILE* f_in = freopen("input.in", "r", stdin);
    // FILE* f_out = freopen("output.out", "w", stdout);
    ll N, T;
    cin >> N >> T;
    
    vector<ll> prefix(N + 1, 0);
    map<ll, ll> mMap;
    ll count = 0;
    mMap[0]++;
    loop_se(i, 1, N) {
        ll v; 
        cin >> v;
        prefix[i] = prefix[i - 1] + v;
        if (mMap[prefix[i] - T]) {
            count += mMap[prefix[i] - T];
        }
        mMap[prefix[i]]++;
    }
    cout << count << endl;
    // fclose(f_in);
    // fclose(f_out);
}

int main() {
    start();
    return 0;
}
