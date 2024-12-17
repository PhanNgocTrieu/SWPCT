#include <bits/stdc++.h>
using namespace std;
void solve() {
	// Solution here
	string math; cin >> math;
	string one = "", two = "", three = "";
	for (auto c : math) {
		if (c == '1') one += "1+";
		else if (c == '2') two += "2+";
		else if (c == '3') three += "3+";
	}
	string output = one + two + three;
	output.pop_back();
	cout << output << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();

	return 0;
}