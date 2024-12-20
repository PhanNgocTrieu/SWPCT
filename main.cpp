#include <iostream>
using namespace std;

int N; // 행성의 수 Number of planets
int W[100000 + 10]; // 행성 질량 Mass of planets

void InputData(void) {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> W[i];
	}
}

int main(void) {
	int ans = -1;

	InputData(); // 입력 Input

	// 코드를 작성하세요 Write from here

	cout << ans << endl; // 출력 Output

	return 0;
}