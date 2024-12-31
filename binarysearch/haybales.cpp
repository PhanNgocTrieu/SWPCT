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
    long long N,Q;
    cin >> N >> Q;

    vector<long long> haybales(N);
    for (long long i = 0; i < N; i++) {
        cin >> haybales[i];
    }

    sort(haybales.begin(), haybales.end());

    for (long long i = 0; i < Q; i++) {
        long long a,b;
        cin >> a >> b;

        auto find = [&](long long x) {
            long long l = 0, r = haybales.size();
            while (l < r) {
                long long m = (l+r)/2;
                if (haybales[m] <= x) {
                    l = m+1;
                } else {
                    r = m;
                }
            }
            return l;
        };
        cout << find(b) - find(a - 1) << endl;
        // long long lower = lower_bound(haybales.begin(), haybales.end(), a) - haybales.begin();
        // long long upper = upper_bound(haybales.begin(), haybales.end(), b) - haybales.begin();
        // cout << upper - lower << endl;
    }
}

int main() {
	setIO("haybales");

    solve();

    return 0;
}