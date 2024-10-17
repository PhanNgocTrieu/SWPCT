// https://codeforces.com/problemset/problem/231/A
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void solve() {
    ll a, b, x, y;
    cin >> a >> b >> x >> y;
    ll diff = abs(b - a);
    diff = min(diff, (abs(a-x) + abs(b-y)));
    diff = min(diff, (abs(a-y) + abs(b-x)));
    cout << diff << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    FILE* f_in = freopen("teleport.in", "r", stdin);
    FILE* f_out = freopen("teleport.out", "w", stdout);
    

    solve();

    fclose(f_in);
    fclose(f_out);
    return 0;
}