// https://usaco.org/index.php?page=viewproblem2&cpid=591
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct t_pair {
    ll x;
    ll y;
};
void solve() {
    vector<t_pair> inp(4);
    vector<ll> res(4, 0);
    for (int i = 0; i < 4; ++i) {
        cin >> inp[i].x >> inp[i].y;
		if (i > 0) {
			if (inp[i].x <= inp[i-1].y) {
				res[i] = inp[i].x;
			}
		}
    }

    for (int i = 1; i < 4;++i) {
        cout << res[i] << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    // FILE* f_in = freopen("promote.in", "r", stdin);
    // FILE* f_out = freopen("promote.out", "w", stdout);
    

    solve();

    // fclose(f_in);
    // fclose(f_out);
    return 0;
}