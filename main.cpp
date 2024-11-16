#include <iostream>
#include <vector>
using namespace std;
#define ll long long
#define MAX_RC	(100)

int R, C;
int xS, yS;
char map[MAX_RC][MAX_RC + 1];

void bfs() {

}

void Input_Data(void) {
	cin >> R >> C;
    bool found = false;
	for (int r = 0; r < R; r++) {
		cin >> map[r];
        if (!found) {
            for (int i = 0; i < C; ++i) {
                if (map[r][i] == 'S') {
                    xS = r;
                    yS = i;
                }
            }
        }
	}
}

class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
		vector<int> ans;
		int l = 0;
		int r = 0;
		int s = nums.size();
		int z = 1;
		for (int i = 1; i < s; ++i) {
			cout << "nums: " << nums[i] << endl;
			if (z == k) { 
				r = i;
				break; 
			}
			if (nums[i] >= nums[i - 1]) {
				cout << __LINE__ << endl;
				l++;
				z = 1;
				ans.push_back(-1);
			}
			else {
				z++;
			}
		}

		// for (int i = l; i < s; ++i) {

		// }

		for (auto a : ans) {
			cout << a << " ";
		}
		cout << endl;

		return ans;
    }
};

class Solution {
public:
    std::vector<int> resultsArray(std::vector<int>& nums, int k) {
        // Skip if k is 1
        if (k == 1) {
            return nums;
        }
        
        int n = nums.size();
        std::vector<int> result;
        int left = 0;
        int right = 1;
        
        while (right < n) {
            // Check if current sequence is not consecutive
            bool is_not_consecutive = nums[right] - nums[right-1] != 1;
            
            if (is_not_consecutive) {
                // Mark invalid sequences
                while (left < right && left + k - 1 < n) {
                    result.push_back(-1);
                    left++;
                }
                left = right;
            }
            // Found valid k-length sequence
            else if (right - left == k - 1) {
                result.push_back(nums[right]);
                left++;
            }
            
            right++;
        }
        
        return result;
    }
};

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int sol = -1;

	// 입력 받는 부분
	// Input_Data();

	vector<int> nums = {2,2,2,2,2};
	Solution{}.resultsArray(nums, 4);


	// 여기서부터 작성

	// 출력 하는 부분
	// cout << sol << '\n';

	return 0;
}