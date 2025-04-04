#include <bits/stdc++.h>
using namespace std;
int N, M;

int check(int m, vector<int> &dt) {
    int s = dt[0] - 1, i = 1;
    for(int j = 1; j < N; j++) {
        s += m;
        while(i < M) {
            if((s <= dt[i] - 1) ) {
                s = max(s, dt[i] -1 );
                i++;
                if(i == M && j < N-1) return 0;
                break;
            }
            else if( s ==  dt[i] || s == dt[i] + 1) {
                i++;
                if(i == M && j < N-1) return 0;
                break;
            }
            else {
                i++;
                if(i == M) return 0;
            }
        }
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    vector<int> dt(M);
    for(int &t: dt)
        cin >> t;
    sort(dt.begin(), dt.end());
    int l =  1, r = (dt[M-1] - dt[0] + 2) / (N - 1), m, c;
    while(l < r - 1) {
        m = (l + r) / 2;
        c = check(m, dt);
        if(c)
            l = m;
        else
            r = m;
    }
    if(check(r, dt)) cout << r;
    else cout << l;
    return 0;
}