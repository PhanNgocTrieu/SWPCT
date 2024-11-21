#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_RC	(100)

int R, C;
char map[MAX_RC][MAX_RC + 1];
int dx[] = {-1 ,1, 0, 0};
int dy[] = {0, 0, -1 ,1};
int sX = 0;
int sY = 0;
int ans = INT_MAX;
struct Pos{
	int x = 0;
	int y = 0;
	int l = 0;
	Pos(int x, int y, int l) : x(x), y(y), l(l) {}
};
// vector<bool> numbers(10, false);
void Input_Data(void) {
	cin >> R >> C;
	for (int r = 0; r < R; r++) {
		cin >> map[r];
		for (int c = 0; c < C; ++c) {
			if (map[r][c] == 'S') {
				sX = r;
				sY = c;
			}
		}
	}
}

int backtrack(vector<vector<bool>> visited, int x, int y, int dis) {
	if (x < 0 && x >= R
	&& y < 0 && y >= C
	&& visited[x][y]
	) {
		return dis;
	}

	visited[x][y] = true;
	auto r = backtrack(visited, x, y + 1, dis + 1);

}

int solve() {
	vector<vector<bool>> visited(R, vector<bool>(C,false));
	ans = min(ans, backtrack(visited, sX, sY, 0));

	return ans;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int sol = -1;

	// 입력 받는 부분
	Input_Data();

	// 여기서부터 작성
	sol = solve();
	// 출력 하는 부분
	cout << sol << '\n';

	return 0;
}