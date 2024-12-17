#include <bits/stdc++.h>
using namespace std;

class Solution {
	struct mark {
		long long index;
		long long value;
	};
public:
    long long findScore(vector<int>& nums) {
		long long scores = 0;
		vector<mark> marks(nums.size());
		vector<bool> mark_bool(nums.size(), false);
		for (int i = 0; i < nums.size(); i++) {
			marks[i].index = i;
			marks[i].value = nums[i];
		}

		sort(marks.begin(), marks.end(), [](const mark&a, const mark&b) {
			if (a.value == b.value) {
				return a.index < b.index;
			}
			return a.value < b.value;
		});

		for (auto v : marks) {
			if (mark_bool[v.index] == true) {
				continue;
			}
			scores += v.value;
			if (v.index > 0) {
				mark_bool[v.index - 1] = true;
			}
			if (v.index < nums.size() - 1) {
				mark_bool[v.index + 1] = true;
			}
		}

		return scores;
    }
};

int main () {
	Solution sol;
	vector<int> nums = {1, 2, 3, 4, 5};
	cout << sol.findScore(nums) << endl;
	return 0;
}