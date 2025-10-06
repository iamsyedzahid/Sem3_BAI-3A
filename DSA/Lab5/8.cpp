#include <iostream>
using namespace std;

bool isSafe(int board[4][4], int row, int col) {
    for (int i = 0; i < row; i++) if (board[i][col]) return false;
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) if (board[i][j]) return false;
    for (int i = row - 1, j = col + 1; i >= 0 && j < 4; i--, j++) if (board[i][j]) return false;
    return true;
}

bool solveFlags(int board[4][4], int row) {
    if (row >= 4) return true;
    for (int col = 0; col < 4; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;
            if (solveFlags(board, row + 1)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int board[4][4] = {0};
    if (solveFlags(board, 0)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) cout << board[i][j] << " ";
            cout << endl;
        }
    } else cout << "No arrangement";
}
