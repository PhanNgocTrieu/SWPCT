#include <bits/stdc++.h>
using namespace std;

condition_variable cinput, coutput, ccalc;
mutex m;

int n;
vector<int> nums;
int outN = 0;
int outM = 0;
bool start = false;

void output()
{
	unique_lock<mutex> lock(m);
	ccalc.wait(lock, []
			   { return outN != 0 && outM != 0; });
	cout << "output: " << outN << " " << outM << endl;
	coutput.notify_all();
}

bool binarySearch(const vector<int> &nums, int s, int target)
{
	int l = s;
	int r = nums.size() - 1;
	while (l <= r)
	{
		int m = l + (r - l) / 2;
		// cout << "l: " << l << " r: " << r << " m: " << m << endl;
		if (nums[m] == target)
		{
			// cout << "found: " << nums[m] << endl;
			return true;
		}
		else if (nums[m] > target)
		{
			r = m - 1;
		}
		else
		{
			l = m + 1;
		}
	}
	return false;
}

void input()
{
	unique_lock<mutex> lock(m);
	cin >> n;
	nums.resize(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> nums[i];
	}
	cinput.notify_all();
}

void solve()
{
	unique_lock<mutex> lock(m);
	cinput.wait(lock, []
				{ return !nums.empty(); });
	cout << "Testcase with input size: " << n << endl;
	int l = 0, r = n - 1;
	outN = 1;
	outM = 1;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); ++i)
	{
		if (binarySearch(nums, i, (nums.size() - 2) / nums[i]))
		{
			outN = nums[i];
			outM = (nums.size() - 2) / nums[i];
			break;
		}
	}
	ccalc.notify_all();
}

int main()
{
	FILE *f_in = freopen("pails.in", "r", stdin);
	FILE *f_out = freopen("pails.out", "w", stdout);
	int t;
	cin >> t;
	while (t--)
	{
		if (!start)
		{
			start = true;
		}
		else
		{
			unique_lock<mutex> lock(m);
			coutput.wait(lock, []
						 { return outN != 0 && outM != 0; });
		}
		thread t1(input);
		thread t2(solve);
		thread t3(output);
		t1.join();
		t2.join();
		t3.join();
	}
	fclose(f_in);
	fclose(f_out);
	return 0;
}