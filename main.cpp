// https://usaco.org/index.php?page=viewproblem2&cpid=666
#include <bits/stdc++.h>
using namespace std;

void setIO(string name = "") {  // name is nonempty for USACO file I/O
	ios_base::sync_with_stdio(0);
	cin.tie(0);  // see Fast Input & Output
	// alternatively, cin.tie(0)->sync_with_stdio(0);
	if (!name.empty()) {
		freopen((name + ".in").c_str(), "r", stdin);  // see Input & Output
		freopen((name + ".out").c_str(), "w", stdout);
	}
}

void solve() {

}

int main() {
	setIO("haybales");

    solve();

    return 0;
}