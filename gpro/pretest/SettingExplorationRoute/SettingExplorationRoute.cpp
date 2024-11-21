#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX_RC	(100)
struct Point {
	int x, y;
};
Point start;
int R, C;
char map[MAX_RC][MAX_RC + 1];
vector<Point> points;
vector<vector<int>> dist;
vector<vector<int>> dp;

vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, -1, 1};

void Input_Data(void) {
	cin >> R >> C;
	for (int r = 0; r < R; r++) {
		cin >> map[r];
		for (int c = 0; c < C; ++c) {
			if (map[r][c] == 'S') {
				start = {r,c};
			}
			else if (map[r][c] != '*' && map[r][c] != '.') {
				points.push_back({r,c});
			}
		}
	}
}

int bfs(Point src, Point dest) {
	vector<vector<int>> distance(R, vector<int>(C, INT_MAX));
	queue<Point> q;
	q.push(src);
	distance[src.x][src.y] = 0;

	while (!q.empty()) {
		auto p = q.front();
		q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];

            if (nx >= 0 && nx < R
			&& ny >= 0 && ny < C
			&& map[nx][ny] != '*'
			&& distance[nx][ny] == INT_MAX) {
                distance[nx][ny] = distance[p.x][p.y] + 1;
                q.push({nx, ny});
            }
        }
	}

	// Get the distance from src to dest
	return distance[dest.x][dest.y];
}

void compute_distances() {
    int n = points.size();
    dist.resize(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < n; ++i) {
        dist[0][i + 1] = bfs(start, points[i]);
        dist[i + 1][0] = dist[0][i + 1];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            dist[i + 1][j + 1] = bfs(points[i], points[j]);
            dist[j + 1][i + 1] = dist[i + 1][j + 1];
        }
    }
}


int tsp(int mask, int pos, int n) {
    if (mask == (1 << (n + 1)) - 1) {
        return dist[pos][0];
    }

    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INT_MAX;
    for (int city = 0; city <= n; ++city) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city, n);
            ans = min(ans, newAns);
        }
    }
    return dp[mask][pos] = ans;
}

int solve() {
    int n = points.size();
    compute_distances();
    dp.resize(1 << (n + 1), vector<int>(n + 1, -1));
    return tsp(1, 0, n);
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