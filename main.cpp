

#include <bits/stdc++.h>
using namespace std;

bool binarySearch(const vector<int>& nums, int s, int target) {
	int l = s;
	int r = nums.size() - 1;
	while (l <= r) {
		int m = l + (r - l) / 2;
		// cout << "l: " << l << " r: " << r << " m: " << m << endl;
		if (nums[m] == target) {
			// cout << "found: " << nums[m] << endl;
			return true;
		} else if (nums[m] > target) {
			r = m - 1;
		} else {
			l = m + 1;
		}
	}
	return false;
}

void solve() {
	int n;
	cin >> n;
	cout << "Testcase with input size: " << n << endl;
	vector<int> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	int l = 0, r = n - 1;
	int outN = 1;
	int outM = 1;
	sort(nums.begin(), nums.end());
	for (auto n : nums) {
		cout << n << " ";
	}
	cout << endl;
	for (int i = 0; i < nums.size(); ++i) {
		if (binarySearch(nums, i, (nums.size() - 2) / nums[i])) {
			outN = nums[i];
			outM = (nums.size() - 2) / nums[i];
			break;
		}
	}

	cout << "output: " << outN << " " << outM << endl;
}

int main() {
	FILE* f_in = freopen("pails.in", "r", stdin);
    FILE* f_out = freopen("pails.out", "w", stdout);
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	fclose(f_in);
    fclose(f_out);
	return 0;
}