/*
    Problem: http://lgedvoj.lge.com/problem/connectedcomponent
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> a[1005];
bool visited[1005];

void travel(int s) {
    queue<int> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v : a[u]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
            }
        }
    }
}

int main() {
    int n,m;
    cin >> n >> m;
    for (int i = 1; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    int ans = 0;
    for (int i = 1; i < m; ++i) {
        if (visited[i] == false) {
            travel(i);
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}