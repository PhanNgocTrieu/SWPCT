#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <algorithm>

using namespace std;

int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};
int ans = 9999999;

void floodRemove(int i, int j, vector<vector<int>>& grid, queue<pair<int, int>>& pos_q) {
	grid[i][j] = 0;
	pos_q.push({i, j});
	queue<pair<int,int>> tmp;
	tmp.push({i,j});
	while (tmp.size() > 0) {
		auto p = tmp.front();
		tmp.pop();
		for (int k = 0; k < 4; ++k) {
			int next_r = p.first + dr[k];
			int next_c = p.second + dc[k];
			if (next_r < 0 && next_r >= grid.size()) continue;
			if (next_c < 0 && next_c >= grid[0].size()) continue;
			if (grid[next_r][next_c] == 1) {
				grid[next_r][next_c] = 0;
				tmp.push({next_r, next_c});
				pos_q.push({next_r, next_c});
			}
		}
	}
}

void floodFillUpdate(const pair<int,int> position, vector<vector<int>>& grid, int color) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<bool>> vs(n, vector<bool>(m,false));
    int curSize = 0;
    queue<pair<int,int>> q;
    q.push({position.first, position.second});
    cout << "pos: " << position.first << " : " << position.second << endl;
    while (q.size() > 0) {
        auto ps = q.front();
        q.pop();
        curSize++;
        // cout << "curSize: " << curSize << endl;
        grid[ps.first][ps.second] = curSize;
        vs[ps.first][ps.second] = true;
        for (int i = 0; i < 4; ++i) {
            int newR = ps.first + dr[i];
            int newC = ps.second + dc[i];
            if (newR < 0 || newR >= grid.size()) continue;
            if (newC < 0 || newC >= grid[0].size()) continue;

            if (grid[newR][newC] == 1
            // && !vs[newR][newC]
            ) {
                cout << "(R,C): (" << newR << "," << newC << ")\n";
                ans = min(ans, grid[newR][newC] - 1);
                break;
            }
            else if (!vs[newR][newC]
            && grid[newR][newC] == 0) {
                vs[newR][newC] = true;
                q.push({newR, newC});
            }
        }
    }
}

int main() {
	long long n,m;
	queue<pair<int, int>> pos_q;
	cin >> n >> m;
	vector<vector<int>> matrix(n, vector<int>(m, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int v; cin >> v;
			matrix[i][j] = v;
		}
	}
	
	bool found = false;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (matrix[i][j] == 1) {
				floodRemove(i, j, matrix, pos_q);
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
	}

    cout << "\nmatrix: " << endl;
    for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << matrix[i][j] << " ";
        }
        cout << endl;
	}

    while (pos_q.size() > 0) {
        auto get_pos = pos_q.front();
        pos_q.pop();
        auto cp = matrix;
	    floodFillUpdate(get_pos, cp, 0);
    }
	
	cout << "ans: " << ans << endl;
	
	return 0;
}
