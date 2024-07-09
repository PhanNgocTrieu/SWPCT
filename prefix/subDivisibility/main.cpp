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
// #define READ_FILE

#ifdef READ_FILE
    FILE* f_in = freopen("input.in", "r", stdin);
    FILE* f_out = freopen("output.out", "w", stdout);
#endif
    ll N;
    cin >> N;
    
    vector<ll> prefix(N + 1, 0);
    map<ll, ll> mMap;
    ll count = 0;
    mMap[0]++;
    loop_se(i, 1, N) {
        ll v; 
        cin >> v;
        prefix[i] = prefix[i - 1] + v;
        prefix[i] %= N;
        if(prefix[i] < 0) prefix[i] += N;
        if (mMap[prefix[i]]) {
            count += mMap[prefix[i]];
        }
        mMap[prefix[i]]++;
    }
    
    cout << count << endl;
#ifdef READ_FILE
    fclose(f_in);
    fclose(f_out);
#endif
}

int main() {
    start();
    return 0;
}
