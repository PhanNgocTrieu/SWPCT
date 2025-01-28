class Solution {
    int ans = 0;
    int m, n;
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};
    
    void dfs(vector<vector<int>>& grid, int r, int c, vector<vector<bool>>& visited) {
        queue<pair<int,int>> q;
        q.push({r,c});
        visited[r][c] = true;
        int sum = 0;
        sum += grid[r][c];
        while (!q.empty()) {
            auto g = q.front();
            q.pop();
            // cout << "g.first: " << g.first << " - g.second: " << g.second << endl;
            for (int i = 0 ; i < 4; ++i) {
                auto nx = dx[i] + g.first;
                auto ny = dy[i] + g.second;
                if (
                    nx >= 0 && nx < m
                    && ny >= 0 && ny < n
                    && !visited[nx][ny]
                    && grid[nx][ny] != 0
                ) {
                    q.push({nx, ny});
                    visited[nx][ny] = true;
                    sum += grid[nx][ny];
                }
            }
        }

        ans = max(ans, sum);
    }
public:
    int findMaxFish(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        vector<vector<bool>> visited(11, vector<bool>(11, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 0 && visited[i][j] == false) {
                    dfs(grid, i, j, visited);
                }
            }
        }

        return ans;
    }
};
