#include <iostream>
#include <vector>
using namespace std;

int N; // 상자의 크기
int Box[150][150];
int maxVal = 0;


int solve() {
    vector<int> sumRows(N,0);
    vector<int> sumCols(N,0);
    // int ans = 0;
    int maxVal = 0;
    // int maxSumR = 0;
    // int maxSumC = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            sumRows[i] += Box[i][j];
        }
        maxVal = max(maxVal, sumRows[i]);
    }
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            sumCols[j] += Box[i][j];
        }
        maxVal = max(maxVal, sumCols[j]);
    }
    int ans = 0;
    for (auto s : sumRows) {
        ans += (maxVal - s);
    }
    int cols = 0;
    for (auto s : sumCols) {
        cols += (maxVal - s);
    }
    return min(ans, cols);
}

void InputData() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Box[i][j];
		}
	}
}
int main() {
	int ans = -1;
	InputData(); // 입력 받는 부분

	// 여기서부터 작성
    ans = solve();

	cout << ans << endl;// 출력하는 부분
	return 0;
}