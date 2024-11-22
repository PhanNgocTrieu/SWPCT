#include <bits/stdc++.h>
using namespace std;

int S, E1, E2;
int ans1, ans2;
vector<int> uoc(10000,2), vs(10000, 1);

int st[4], e1[4], e2[4];

void extra(int s, int *e) {
    for(int i = 0; i < 4; i++) {
        e[i] = s % 10;
        s /= 10;
    }
}

void InputData()
{
	cin >> S >> E1 >> E2;
    for(int i = 2; i < 5000; i++)
        for(int j = i * 2; j < 10000; j += i)
            uoc[j]++;
    extra(S, st); extra(E1, e1); extra(E2,e2);
    vs[S] = 0;
}

int main()
{
	InputData();
    

	int dp[10][10][10][10];
    dp[st[0]][st[1]][st[2]][st[3]] = 0;
    int q[10000][4];
    for(int i = 0; i < 4; i++) q[0][i] = st[i];
    int s = 0, e = 1, l, count = 0;
    while(s < e) {
        int x = q[s][3] * 1000 + q[s][2] * 100 + q[s][1] * 10 + q[s][0];
        l = 1;
        //count++;
        //cout << x << endl;
        for(int k = 0; k < 4; k++) {
            for(int i = (k == 3); i < 10; i++) {
                int y = x + (i - q[s][k])*l;
                if(i != q[s][k] && vs[y] ==  1 && abs(uoc[x] - uoc[y]) <=  1) {
                    vs[y] = 0;
                    for(int j = 0; j < 4; j++)
                        q[e][j] = q[s][j];
                    q[e][k] = i;
                    dp[q[e][0]][q[e][1]][q[e][2]][q[e][3]] = dp[q[s][0]][q[s][1]][q[s][2]][q[s][3]] + 1;
                    e++;
                }
            }
            l *= 10;
        }
        s++;
    }
	cout << dp[e1[0]][e1[1]][e1[2]][e1[3]] << '\n';// 출력하는 부분
	cout << dp[e2[0]][e2[1]][e2[2]][e2[3]] << '\n';
	return 0;
}