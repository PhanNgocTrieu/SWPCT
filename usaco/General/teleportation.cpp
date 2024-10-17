// https://codeforces.com/problemset/problem/231/A
#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
void solve() {
    ll a, b, x, y;
    cin >> a >> b >> x >> y;
    ll res = x > y ? abs(y - a) + abs(b - x) : abs(x - a) + abs(b - y);
    ll without = abs(b - a);
    cout << min(res, without) << endl;
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