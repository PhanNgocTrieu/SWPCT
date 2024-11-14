#include <iostream>
#include <vector>
using namespace std;
#define ll long long
#define MAX_RC	(100)

int R, C;
int xS, yS;
char map[MAX_RC][MAX_RC + 1];

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

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int sol = -1;

	// 입력 받는 부분
	Input_Data();

	// 여기서부터 작성

	// 출력 하는 부분
	cout << sol << '\n';

	return 0;
}