#include <bits/stdc++.h>
using namespace std;

int N, r = 0, c = 0, mnr = 1000, mxr = 0, mnc = 1000, mxc = 0, R, C;
string Info;
int sol = -1;
int dx[4] = {0,0,1,-1}, dy[4] = {1,-1,0,0};

void InputData(void) {
	cin >> N;
	cin >> Info;
	for(char ch: Info) {
        if(ch == '2') mxr = max(mxr, ++r);
        else if(ch == '3') mnr = min(mnr, --r);
        else if(ch == '1') mnc = min(mnc, --c);
        else if(ch == '0') mxc = max(mxc, ++c);
    }
    //cout << mnr << ' ' << mxr << ' ' << mnc << ' ' << mxc << '\n';

}

bool bfs(int r, int c, vector<vector<int>> &dp, vector<vector<int>> &dt) {
    queue<int> qr, qc;
    qr.push(r); qc.push(c);
    dp[r][c] = 0;
    bool ok = true;
    int x, y;
    while(!qc.empty()){
        c = qc.front(); qc.pop();
        r = qr.front(); qr.pop();
        for(int i = 0; i < 4; i++) {
            x = r + dx[i];
            y = c + dy[i];
            if(x == -1 && dt[r][c] == 0) ok =  false;
            if(y == -1 && dt[r][c] == 0) ok =  false;
            if(x == R && dt[x][c] == 0) ok = false;
            if(y == C && dt[r][y] == 0) ok = false;
            if( x == -1 || y == -1 || x == R || y == C) continue;
            if(dp[x][y] == 0) continue;
            if(dt[x][y] == 1) continue;
            qc.push(y);
            qr.push(x);
            dp[x][y] = 0;
        }
    }

}

void debug(vector<vector<int>> &dp) {
    cout << "===================================\n";
    for(int r = 0; r <= R; r++) {
        for(int c = 0; c <= C; c++){
            cout << dp[r][c] << ' ';
        }
        cout << '\n';
    }
    
    cout << "===================================\n";
}

int main(void) {
	InputData();
    
    R =  mxr - mnr;
    C = mxc - mnc;
    c = -mnc; r = -mnr;
    vector<vector<int>> dt(R+1, vector<int>(C+1, 0));
    vector<vector<int>> dp(R+1, vector<int>(C+1, 1));
	for(char ch: Info) {
        if(ch == '2') r++;
        else if(ch == '3') --r;
        else if(ch == '1') --c;
        else if(ch == '0') ++c;
        dt[r][c] = 1;
    }
    int ans = 0;
    debug(dt);
    for(r = 0; r < R; r++) {
        for(c = 0; c < C; c++){
            //cout << dt[r][c] << ' ';
            if(dp[r][c]) {
                if(bfs(r, c, dp, dt))
                    ans++;
                debug(dp);
            }
        }
        //cout << '\n';
    }
    cout << ans << endl;
	return 0;
}