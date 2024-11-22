#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

#define MAX_RC	(100)
#define oo	1000000000

int R = 4, C = 4, sr, sc, N;
char map[MAX_RC][MAX_RC + 1];
vector<pair<int,int>> ex(1);
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void Input_Data(void) {
	cin >> R >> C;
	for (int r = 0; r < R; r++) {
		cin >> map[r];
		for(int c = 0; c < C; c++) {
				if('1' <= map[r][c] && map[r][c] <= '9')
					ex.push_back({r,c});
				if('S' == map[r][c]) {
					ex[0].first = r;
					ex[0].second = c;
				}
		}
	}
    N = ex.size();
}

void BFS(int r, int c, vector<int>& res) {
	vector<vector<int>> d(R, vector<int>(C,oo));
	d[r][c] = 0;
	queue<int> qr, qc;
	qr.push(r); qc.push(c);
    int x, y;
    while(!qc.empty()) {
        c =  qc.front(); qc.pop();
        r = qr.front(); qr.pop();
        for(int i = 0; i < 4; i++) {
            x = c + dx[i];
            y = r + dy[i];
            if(x < 0 || y < 0 ||  x >=  C || y >= R) continue;
            if(d[y][x] == oo && map[y][x] != '*') {
                d[y][x] = d[r][c] + 1;
                qc.push(x);
                qr.push(y);
            }
        }
    }
    for(int i = 0; i < N; i++) 
        res[i] = d[ex[i].first][ex[i].second];
}



int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int sol = oo;

	Input_Data();
    vector<vector<int>> dt(N, vector<int>(N, oo)), dp( 1 << N, vector<int>(N, oo));
    for(int i = 0; i < N; i++) {
        BFS(ex[i].first, ex[i].second, dt[i]);
    }
    int M = 1 << N;
    dp[1][0] = 0;
    for(int i = 1; i < M; i++) {
        for(int j = 0; j < N; j++) {
            if( i & (1 << j))
                for(int k = 1; k < N; k++)
                    if((~i) & (1 << k)) {
                        int mask = i | (1 << k);
                        dp[mask][k] = min(dp[mask][k], dp[i][j] + dt[j][k]);
                    }
                        
        }
    }
    for(int k = 1; k < N; k++)
        sol =  min(sol, dp[M-1][k] + dt[k][0]);



	cout << sol << '\n';

	return 0;
}