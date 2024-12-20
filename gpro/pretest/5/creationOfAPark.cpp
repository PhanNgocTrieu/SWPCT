#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;
#define MAXN (100)
int N;
char map[MAXN + 10][MAXN + 10];
bool visited[MAXN + 10][MAXN + 10];

char ans;//구매자 이름 Buyer's name
int areacnt;//구매자 영역 개수 Number of buyer's area
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
unordered_map<char, pair<int, int>> area;

void InputData() {
	cin >> N;
	for (int h = 0; h < N; h++) {
		cin >> map[h];
	}
    area['R'] = { 0, 0 };
    area['G'] = { 0, 0 };
    area['B'] = { 0, 0 };
}

void walkthrough(int i, int j, char target) {
    queue<pair<int, int>> q;
    q.push({ i, j });
    int count = 0;
    while (!q.empty()) {
        auto cur = q.front();
        count++;
        q.pop();
        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (visited[nx][ny] || map[nx][ny] != target) continue;
            visited[nx][ny] = true;
            q.push({ nx, ny });
        }
    };
    area[target] = { area[target].first + 1, area[target].second < count ? count : area[target].second };
    // std::cout << "area[" << target << "] = { " << area[target].first << ", " << area[target].second << " }\n";
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) {
                // std::cout << "walkthrough(" << i << ", " << j << ", " << map[i][j] << ")\n";
                walkthrough(i, j, map[i][j]);
            }
        }
    }

    int cur_numbers = 0;
    char cur_char = 'R';
    int cur_lands = 0;
    for (auto a : area) {
        if (a.second.first > cur_numbers) {
            cur_numbers = a.second.first;
            cur_char = a.first;
            cur_lands = a.second.second;
        }
        else if (a.second.first == cur_numbers) {
            if (a.second.second > cur_lands) {
                cur_char = a.first;
                cur_lands = a.second.second;
            }
        }
    }

    ans = cur_char;
    areacnt = cur_numbers;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	InputData();// 입력받는 부분 Input

	// 여기서부터 작성 Write from here
    solve();

	cout << ans << " " << areacnt << "\n";// 출력하는 부분 Output
	return 0;
}