//BeginCodeSnip{C++ Short Template}
#include <bits/stdc++.h> // see /general/running-code-locally
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using pi = pair<int,int>;
#define f first
#define s second
#define mp make_pair

void setIO(string name = "") {
	cin.tie(0)->sync_with_stdio(0); // see /general/fast-io
	if (sz(name)) {
		freopen((name + ".in").c_str(), "r", stdin); // see /general/input-output
		freopen((name + ".out").c_str(), "w", stdout);
	}
}
//EndCodeSnip

int main() {
	setIO();
	int n, t, ans = 0;
	cin >> n >> t;
	vi nums(n);
	for (int i = 0; i < n; i++) { cin >> nums[i]; }

	int left = 0, right = 0, cur = 0;
	while (left < n && right < n) {
		// Finding the maximum right for which cur is less than t.
		while (right < n) {
			cur += nums[right++];
			// Subtracting the exceeded book from cur.
            if (cur == t) {
                ans++;
            }
			else if (cur > t) {
				cur -= nums[--right];
				break;
			}
		}
		cur -= nums[left++];
	}

	cout << ans;
}
