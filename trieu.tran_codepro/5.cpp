#include <iostream>
#include <queue>
using namespace std;
#define MAXN (100)
int N;
char map[MAXN + 10][MAXN + 10];
int block[3] = {0, 0,0}, zones[3] = {0,0,0}, dx[4] = {1, -1, 0,0}, dy[4] = {0,0, 1, -1};

char ans;
int areacnt;

void InputData() {
	cin >> N;
	for (int h = 0; h < N; h++) {
		cin >> map[h];
	}
}

void BFS(int r, int c) {
    char a = map[r][c];
    int id = 0, x, y;
    if(a == 'G') id = 1;
    else if(a =='B') id = 2;
    zones[id]++;
    queue<int> qr, qc;
    qr.push(r); qc.push(c);
    while(!qc.empty()) {
        r = qr.front(); qr.pop();
        c = qc.front(); qc.pop();
        block[id]++;
        for(int i = 0; i < 4; i++) {
            x = r + dx[i];
            y = c + dy[i];
            if( x < 0 || x >= N || y < 0 || y >= N) continue;
            if(map[x][y] == a) {
                map[x][y] = 0;
                qr.push(x);
                qc.push(y);
            }
        }
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	InputData();

    for (int h = 0; h < N; h++) {
		for(int w = 0; w < N; w++) {
            if(map[h][w] != 0) {
                BFS(h, w);
            }
        }
	}
    int k = 0;
    for(int i = 1; i < 3; i++) {
        if(zones[i] > zones[k] || (zones[i] == zones[k] && block[i] > block[k])) k = i;
    }
    if(k == 0) cout << 'R';
    else if(k == 1) cout << 'G';
    else cout << 'B';

    cout << ' ' << zones[k];


	//cout << ans << " " << areacnt << "\n";
	return 0;
}