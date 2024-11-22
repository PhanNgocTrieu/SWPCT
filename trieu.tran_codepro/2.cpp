#include <iostream>
using namespace std;

int N; // 상자의 크기
int Box[150][150];

void InputData() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Box[i][j];
		}
	}
}
int main() {
	int ans = -1, col, row, mx = 0, sum = 0;
	InputData(); // 입력 받는 부분

	for (int i = 0; i < N; i++) {
		col = row = 0;
		for (int j = 0; j < N; j++) {
			row += Box[i][j];
			col += Box[j][i];
		}
		sum += col;
		mx = max(mx, max(col, row));
	}
	ans = mx * N - sum;
	
	cout << ans << endl;// 출력하는 부분
	return 0;
}