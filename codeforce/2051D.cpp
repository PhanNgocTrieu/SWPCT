#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// #define SLOW_ONE
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

// This would be O(n^2) solution
ll n, x, y;
vector<ll> a(n);

bool valid(ll v, ll x, ll y) {
	if (v >= x && v <= y) {
		return true;
	}
	return false;
}

ll calLessThanX(ll lx, ll sum) {
	ll count = 0;
	int j = 0;
	for (int i = n - 1; i >= 0; --i) {
		while (j < n && sum - a[i] - a[j] >= lx) {
			j++;
		}
		count += (n - j);
	}

	for (int i = 0; i < n; i++) {
		if (sum - a[i] - a[i] < lx) {
			count--;
		}
	}
	return count;
}

void solve() {
	cin >> n >> x >> y;
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	ll sum = 0;
	for (auto i : a) {
		sum += i;
	}
#ifdef SLOW_ONE
	ll count = 0;
	for (int j = n - 1; j >= 0; --j) {
		for (int k = 0; k < j; ++k) {
			if (valid( (sum - a[j] - a[k]), x, y)) {
				count++;
			}
		}
	}
	cout << count << endl;
#endif
	sort(a.begin(), a.end());
	ll lessY = calLessThanX(y + 1, sum);
	ll lessX = calLessThanX(x, sum);
	cout << "lessY: " << lessY << " lessX: " << lessX << endl;
	cout << lessY - lessX << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t; cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}