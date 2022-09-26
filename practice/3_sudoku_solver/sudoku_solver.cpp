#include <iostream>
#include <vector>
using namespace std;


class Solution {
private:
    // void printBoard(vector<vector<char>>& board) {

    // }

    bool check(vector<vector<char>>& board, int i, int j, char val) {
        int row = i - i%3, col = j - j%3;
        // check column and row
        for(int x=0; x<9; x++) if(board[x][j] == val) return false;
        for(int y=0; y<9; y++) if(board[i][y] == val) return false;

        // check sub-boxes 3x3
        for (int x = 0; x<3; x++)
            for (int y = 0; y<3; y++)
                if (board[x + row][y + col] == val) return false;
        
        return true;
    }
    bool solve(vector<vector<char>>& board, int i, int j) {
        if (i == 9) return true;
        if (j == 9) return solve(board, i + 1, 0);
        if (board[i][j] != '.') return solve(board, i, j + 1);

        for (char c = '1'; c <= '9'; c++) {
            if (check(board, i, j, c)) {
                board[i][j] = c;
                if (solve(board, i, j + 1)) return true;
                board[i][j] = '.';
            }
        }

        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board, 0, 0);
    }
};

int main() {
    vector<vector<char>> board =    {{'5','3','.','.','7','.','.','.','.'}
                                    ,{'6','.','.','1','9','5','.','.','.'}
                                    ,{'.','9','8','.','.','.','.','6','.'}
                                    ,{'8','.','.','.','6','.','.','.','3'}
                                    ,{'4','.','.','8','.','3','.','.','1'}
                                    ,{'7','.','.','.','2','.','.','.','6'}
                                    ,{'.','6','.','.','.','.','2','8','.'}
                                    ,{'.','.','.','4','1','9','.','.','5'}
                                    ,{'.','.','.','.','8','.','.','7','9'}};

    Solution solution;
    solution.solveSudoku(board);

    return 0;
}