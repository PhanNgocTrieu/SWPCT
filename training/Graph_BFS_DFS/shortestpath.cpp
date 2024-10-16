/**
 * @file shortestpath.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 * @a http://lgedvoj.lge.com/problem/simplespmatrix
 */

/*
    Problem: http://lgedvoj.lge.com/problem/connectedcomponent
*/
#include <bits/stdc++.h>
using namespace std;

// vector<int> a[1005];
int n,m;
bool visited[105][105];
char a[105][105];
int sx, sy;
int xd, yd;
// int dx, dy;
int d[105][105]; // distance
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

bool isValid(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m) {
        return false;
    }
    return true;
}

void BFS(int sx, int sy) {
    queue<pair<int,int>> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    d[sx][sy] = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dx[i];

            if (
                isValid(newX, newY) &&
                a[newX][newY] != '+' &&
                !visited[newX][newY]
            ) {
                q.push({newX, newY});
                visited[newX][newY] = true;
                d[newX][newY] = d[x][y] + 1;
            }
        }
    }
}

int main() {
    int ans = -1;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            if (a[i][j] == 'S') {
                sx = i;
                sy = j;
            }
            else if (a[i][j] == 'D') {
                xd = i;
                yd = j;
            }
        }
    }

    BFS(sx, sy);
    cout << (d[xd][yd] == 0 ? -1 : d[xd][yd]) << endl;
    return 0;
}