#include <bits/stdc++.h>
using namespace std;

int N;
int K;

bool check(vector<int> &X, int v) {
    int current = X[0] + 2 * v, count = 1;
    for(int i = 1; i < N; i++) {
        if(X[i] > current) {
            current = X[i] + 2 * v;
            count++;
        }
    }
    
    return count <= K;
}
int main() {
	int ans = -1;
	cin >> N >> K;
    vector<int> X(N);
	for (int i = 0; i < N; i++) {
		cin >> X[i];
	}
    sort(X.begin(), X.end());
    int l = 0, r = (X[N-1] - X[0] + K - 1) / K, m;
    while(l < r - 1) {
        m =  (l + r) / 2;
        if(check(X, m)) r = m;
        else l = m;
    }
    if(check(X,l))
        cout << l;
    else cout << r;
	return 0;
}