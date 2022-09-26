#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<set<int>> row(9), col(9), box(9);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    continue;
                }
                int num = board[i][j] - '0';
                if (row[i].count(num) || col[j].count(num) || box[(i/3)*3 + j/3].count(num)) 
                    return false;

                row[i].insert(num);
                col[j].insert(num);
                box[(i/3)*3 + j/3].insert(num);
            }
        }

        return true;
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
    bool hehe = solution.isValidSudoku(board);
    if (hehe) cout << "Valid Sudoku" << endl;
    else cout << "Invalid Sudoku" << endl;

    return 0;
}