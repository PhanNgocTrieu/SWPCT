// https://codepro.lge.com/exam/19/overseas-questions-for-previous-test/quiz/11

#include<bits/stdc++.h>
using namespace std;
 
int n, m, u, v, w;
int a[105][105];
int oo = 1e9;
int minPath[105][105];
 
struct node {
    int u; // Vertice id
    int w; // Weight (for Dijkstra using priority_queue)
};
 
void dijkstra(int s) {
    // d[i][j] is the minumum cost from source [0,0] to location [i][j]
    int d[110];
    for (int i = 1; i <= n; i++) {
        d[i] = oo;
    }
     
    // Setup priority queue
    auto comparator = [](const node& a, const node& b) {
        return a.w > b.w;
    };
    priority_queue<node, vector<node>, decltype(comparator)> q(comparator);
    q.push({s, 0}); // add source to queue
    d[s] = 0; // the cost from source to source is 0
     
    while (!q.empty()) {
        // get the minimum node from priority_queue
        int u = q.top().u;
        int w = q.top().w;
        q.pop();
        for (int v = 1; v <= n; v++) {
            if (a[u][v] == oo) continue;
            // v la dinh lien ke
            if (d[v] > d[u] + a[u][v]) {
                // new_node's current cost is larger, update better cost by moving from current_node
                d[v] = d[u] + a[u][v];
                q.push({v, d[v]}); // and add new node to queue
            }
        }
    }
    for (int i = 1; i <= n; i++) minPath[s][i] = d[i];
}
 
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = oo;
        }
    }
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        a[u][v] = w;
        a[v][u] = w;
    }
    for (int i = 1; i <= n; i++) dijkstra(i);
    int ans = oo;
    for (int i = 1; i <= n; i++) {
        int maxx = 0;
        for (int j = 1; j <= n; j++) {
            maxx = max(maxx, minPath[i][j]);
        }
        ans = min(ans, maxx);
    }
    cout << ans;
    return 0;
}