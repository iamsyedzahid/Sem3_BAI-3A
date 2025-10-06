//Q1.c.
#include <iostream>
using namespace std;

bool solveMaze(int maze[4][4], int x, int y, int sol[4][4], int tx, int ty) {
    if (x < 0 || y < 0 || x >= 4 || y >= 4 || maze[x][y] == 0) return false;
    sol[x][y] = 1;
    if (x == tx && y == ty) return true;
    if (solveMaze(maze, x + 1, y, sol, tx, ty) ||
        solveMaze(maze, x, y + 1, sol, tx, ty) ||
        solveMaze(maze, x - 1, y, sol, tx, ty) ||
        solveMaze(maze, x, y - 1, sol, tx, ty)) return true;
    sol[x][y] = 0;
    return false;
}

int main() {
    int maze[4][4] = {
        {1, 1, 1, 1},
        {0, 0, 0, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 1}
    }, sol[4][4] = {0};
    if (solveMaze(maze, 0, 0, sol, 2, 0)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) cout << sol[i][j] << " ";
            cout << endl;
        }
    } else cout << "No path found";
}
