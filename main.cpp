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
    FILE* f_in = freopen("input.in", "r", stdin);
    FILE* f_out = freopen("output.out", "w", stdout);
    ll N, T;
    cin >> N >> T;
    
    vector<ll> prefix(N + 1, 0);
    vector<ll> origin(N, 0);
    map<ll, ll> mMap;
    ll count = 0;
    mMap[0]++;
    loop_se(i, 1, N) {
        ll v; 
        cin >> v;
        origin[i - 1] = v;
        prefix[i] = prefix[i - 1] + v;
        mMap[prefix[i]]++;

        // if (v == T) {
        //     count++;
        // }
    }
    // cout << endl;
    print_vt(origin);
    print_vt(prefix);

    for (auto e : mMap) {
        cout << e.first << ":" << e.second << endl;
    }
    loop_se(i, 1, N) {
        // if ()
        int value = prefix[i];
        int getNum = mMap[prefix[i - 1]];
        count += getNum;    
        // if (prefix[i] != 0) {
            if (mMap[prefix[i] - T]) {
                count += mMap[prefix[i] - T];
                // mMap[prefix[i] - T] = 0;
                cout << prefix[i] - T << " -> " << i << endl; 
            }
        // }
    }
    cout << count << endl;
    fclose(f_in);
    fclose(f_out);
}

/*
    [0]:    0
    [2]:    1
    [1]:    1
    [4]:    1
    [9]:    1
    [7]:    1
*/

int main() {
    start();
    return 0;
}
