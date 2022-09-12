#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

vector<pair<int,int>> directions = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};

void printBoard(int ** board,  int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(2) << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool solve(int ** board, int n, int currentStep, pair<int, int> coordinate) {
    // if find a solution
    if (currentStep == n*n +1) {
        printBoard(board, n);
        return true;
    }
    // if coordinate is invalid or duplicate previous step
    if (coordinate.first < 0 || coordinate.first >= n || coordinate.second < 0 ||
        coordinate.second >= n || board[coordinate.first][coordinate.second])
        return false;

    // if the next step is satisfy the condition
    board[coordinate.first][coordinate.second] = currentStep++;

    // recursion until finds a solution
    for (auto & p: directions) {
        if (solve(board, n, currentStep, {coordinate.first + p.first, coordinate.second + p.second}))
            return true;
    }

    // back tracking 
    board[coordinate.first][coordinate.second] = 0;

    return false;
}

void KnightTour(int n) {
    // initialize the board
    int ** board = new int*[n];
    for(int i = 0; i < n; i++)
    {
        board[i] = new int[n];
        for(int j = 0; j < n; j++)
            board[i][j] = 0;
    }

    // call solve function
    solve(board, n, 1, {0, 0});
}

int main() {
    int n;
    cout << "Enter the size of board: ";
    cin >> n;
    KnightTour(n);

    return 0;
}