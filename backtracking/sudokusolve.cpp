#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<char>> vc;
 
class Solution {
public:
 
    bool isValidValue(int i, int j, vc& board, char num) {
        int n = board.size();
        for (int k = 0; k < n; k++) {
            // Row check
            if (board[i][k] == num)
                return false;
            // Column check
            if (board[k][j] == num)
                return false;
        }
         
        // Check in the small 3x3 matrix
        int s = sqrt(n);
        int startRow = i - i % s;
        int startCol = j - j % s;
         
        for (int r = startRow; r < startRow + s; r++) {
            for (int c = startCol; c < startCol + s; c++) {
                if (board[r][c] == num)
                    return false;
            }
        }
         
        return true;
    }
 
    bool backtracking(vc& board) {
        int n = board.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') {
                    for (char num = '1'; num <= '9'; num++) {
                        if (isValidValue(i, j, board, num)) {
                            board[i][j] = num;
                            if (backtracking(board)){
                                return true;
                            }
                            board[i][j] = '.'; // Backtrack
                        }
                    }
                    return false;
                }
            }
        }
         
        return true;
    }
 
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);
    }
};