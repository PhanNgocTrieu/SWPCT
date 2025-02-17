// https://vjudge.net/contest/691170#problem/A
#include <bits/stdc++.h>

using namespace std;

#define ll long long


/*
    Algorithm:
        N = 5, Tmax = 8;
            [4, 8 ,7 ,6, 4]

            greater<ll> pq;

            if m = 3:
                pq = {4 7 6}
                    (adding 6 element) pq = {8 7 10}
                    (adding 4 element) pq = {7 10 14}
                => 14 <= 8 => false

            if m = 4:
                pq = {4 8 7 6}
                    (adding 4 element) pq = {4 6 7 8 8}

                => last cow finish at (8 <= 8) => true
*/

void solve() {

}

#define READ_FILE
#define FILE_I "convention.in"
#define FILE_O "convention.out"

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