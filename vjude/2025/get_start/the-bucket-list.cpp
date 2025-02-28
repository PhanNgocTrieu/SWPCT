// https://vjudge.net/contest/690982#problem/E
#include <bits/stdc++.h>

using namespace std;

#define ll long long

/*
3
4 10 1
8 13 3
2 6 2

        [1  2  3  4  5  6  7  8  9  10  11  12  13]
[0]              [s]
[1]                          [s]                [e]
[2]        [s]         [e]          [e]
---------------------------------------------------
           [2]   [3]   [1]   [4]    [3]         [1]

*/

class Compare {
public:
    bool operator() (pair<ll,ll> a, pair<ll,ll> b) {
        // if (a.first == b.first) {
        //     return a.second > b.second;
        // }
        return a.first >= b.first;
    }
};

void solve() {
    ll n; cin >> n;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, Compare> pq;
    for (int i = 0; i < n; i++) {
        ll s, e, b; cin >> s >> e >> b;
        pq.push({s, b});
        pq.push({e, -b});
    }
    ll ans = 0;
    ll cur_buck = 0;
    while (!pq.empty()) {
        auto top = pq.top();
        // cout << "pq.top().first: " << top.first << " pq.top().second: " << top.second << endl;
        pq.pop();
        cur_buck += top.second;
        ans = max(ans, cur_buck);
    }

    cout << ans << endl;
}

#define READ_FILE
// #define ASSIGNMENT

#ifndef ASSIGNMENT
#define FILE_I "./file/blist.in"
#define FILE_O "./file/blist.out"
#else
#define FILE_I "blist.in"
#define FILE_O "blist.out"
#endif

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#ifdef READ_FILE
    auto f_i = freopen(FILE_I, "r", stdin);
    auto f_o = freopen(FILE_O, "w", stdout);
#endif

    // int t; cin >> t;
    // while (t--) {
        solve();
    // }

#ifdef READ_FILE
    fclose(f_i);
    fclose(f_o);
#endif
    return 0;
}