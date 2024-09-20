// https://codeforces.com/problemset/problem/546/A
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void solve() {
    ll k, n, w;
	cin >> k >> n >> w;
	ll borrows = 0;
	ll i = 1;
	while (i <= w){
		borrows += (i++) * k;
	}
	if (n >= borrows)
		cout << 0 << endl;
	else 
		cout << (borrows - n) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    //FILE* f_in = freopen("teleport.in", "r", stdin);
    //FILE* f_out = freopen("teleport.out", "w", stdout);
    

    solve();

    //fclose(f_in);
    //fclose(f_out);
    return 0;
}