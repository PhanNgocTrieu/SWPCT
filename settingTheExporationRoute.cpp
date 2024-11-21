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
int ans = 0;
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
	}
}

void findS() {
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (map[i][j] == 'S') {
				sX = i;
				sY = j;
				return;
			}
		}
	}
}

void bfs() {
	bool numbers[MAX_RC][MAX_RC + 1];
	bool foundNumber = false;
	bool endPoint = false;
	Pos* v = new Pos({sX, sY, 0});
	do {
		if (v == nullptr) {
			break;
		}
		cout << "work at: (x,y): " << v->x << ", " << v->y << '\n';
		foundNumber = false;
		int disMin = INT_MAX;
		queue<Pos> q;
		q.push(*v);
		cout << "ans += " << v->l << " -> ans = " << ans << '\n';
		ans += v->l;
		{
			if (!endPoint) {
				numbers[v->x][v->y] = true;
			}
			delete v;
			v = nullptr;
		}
		bool visited[MAX_RC][MAX_RC + 1];
		while (!q.empty()) {
			auto p = q.front();
			q.pop();
			visited[p.x][p.y] = true;
			cout << " p of (x,y): " << p.x << "," << p.y << '\n';
			for (int i = 0; i < 4; ++i) {
				int nx = p.x + dx[i];
				int ny = p.y + dy[i];
				int nl = p.l + 1;
				if (
					nx >= 0 && nx < R &&
					ny >= 0 && ny < C &&
					map[nx][ny] != '*' &&
					visited[nx][ny] == false &&
					numbers[nx][ny] == false
				) {
					if (endPoint) {
						if (map[nx][ny] == 'S') {
							if (ans > nl) {
								ans += nl;
							}
						}
					}
					else {
						visited[nx][ny] = true;
						if (map[nx][ny] != '.') {
							foundNumber = true;
							if (v == nullptr)
								v = new Pos({nx, ny, nl});
							else {
								if (nl < disMin) {
									v->x = nx;
									v->y = ny;
									v->l = nl;
									disMin = nl;
								}
							}
						}
					}
					q.push({nx, ny, nl});
				}
			}
		}

		if (!foundNumber) {
			endPoint = true;
		}

	} while (foundNumber || endPoint);

}

int solve() {
	findS();
	bfs();
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