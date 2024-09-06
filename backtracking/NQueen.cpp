/**
 * @brief https://leetcode.com/problems/n-queens/description/
 * 
 */
#include <bits/stdc++.h>
using namespace std;
class Solution {
    void fillRowAndCol() {

    }

    void fillAngle() {
        
    }
    public:
        vector<vector<string>> solveNQueens(int n) {
            vector<vector<string>> res;
            vector<vector<bool>> exist(n, vector<bool>(n, false));
            
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; j++) {
                    if (!exist[i][j]) {
                        if (backtracking(res, exist, i, j)) {
                            break;
                        }
                    }
                }
            }
        }

        bool backtracking(vector<vector<string>>& res,
            vector<vector<bool>> exist,
            int i, int j
        ) {
            if ()
        }
}