/*
    Links: https://codeforces.com/problemset/problem/991/C
*/

#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <vector>

using namespace std;

#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f
#define ll long long

using s = std:: string;
using vll = vector<ll>;
using vb = vector<bool>;
using mll = map<ll,ll>;
using umll = unordered_map<ll,ll>;
using pll = pair<ll,ll>;
using pls = pair<ll,s>;
using vpll = vector<pair<ll,ll>>;

// debug templates
#define p(x, n) pow(x, n)
#define d(x) (x)*(x)

// #define READ_FILE
// #define TESTCASE 

using vvll = vector<vector<ll>>;
using vvb = vector<vector<bool>>;

ll dc[] = {1, -1, 0, 0};
ll dr[] = {0, 0, 1, -1};
ll floodSize = 0;
ll n, sx, sy, dx, dy;
queue<pair<ll,ll>> pos_q;
vector<vector<char>> land(55, vector<char>(55,'0'));
queue<pair<int, int>> qp;
ll ans = INT_MAX;
bool found = false;

#define cel(n,k) ((n-1)/k+1)

bool can(ll i) {
    ll tmp = n;
    ll cnt = 0;

    while (1) {
        if (tmp - i <= 0) {
            cnt += tmp;
            break;
        }

        tmp -= i;
        cnt += i;
        tmp -= tmp/10;
    }

    return cnt >= cel(n,2);
}

void solve() {
    cin >> n;
    ll left = 1;
    ll right = 1e18;
    while (left < right) {
        ll mid = (left + right) / 2;
        if (can(mid)) { // If fit
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    cout << left << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

#ifdef READ_FILE
    FILE* f_in = freopen("pairup.in", "r", stdin);
    FILE* f_out = freopen("pairup.out", "w", stdout);
#endif

#ifdef TESTCASE
    ll ts;
    cin >> ts;
    while (ts--) {
        solve();
    }
#else
    solve();
#endif

#ifdef READ_FILE
    fclose(f_in);
    fclose(f_out);
#endif
    return 0;
}
