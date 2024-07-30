/*
  Issue: https://leetcode.com/problems/find-if-path-exists-in-graph/description/
*/

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        ios::sync_with_stdio(0);
        cin.tie(0); cout.tie(0);
        vector<int> adj[n];
        for (auto itr : edges) {
            adj[itr[0]].push_back(itr[1]);
            adj[itr[1]].push_back(itr[0]);
        }

        vector<bool> vis(n, 0);
        queue<int> q;
        q.push(source);
        vis[source] = 1;
        while (!q.empty()) {
            int top = q.front();
            q.pop();
            for (auto it : adj[top]) {
                if (!vis[it]) {
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }

        return vis[destination];
    }
};
