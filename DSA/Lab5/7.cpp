#include <iostream>
using namespace std;

#define N 5

int maze[N][N] = {
    {1,0,1,0,1},
    {1,1,1,1,1},
    {0,1,0,1,1},
    {1,0,0,1,1},
    {1,1,1,0,1}
};

int sol[N][N] = {0};

bool solve(int x, int y) {
    if (x == N-1 && y == N-1) {
        sol[x][y] = 1;
        return true;
    }
    if (x >= 0 && y >= 0 && x < N && y < N && maze[x][y] == 1 && sol[x][y] == 0) {
        sol[x][y] = 1;
        if (solve(x+1, y) || solve(x, y+1) || solve(x-1, y) || solve(x, y-1))
            return true;
        sol[x][y] = 0;
    }
    return false;
}

int main() {
    if (solve(0, 0)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << sol[i][j] << " ";
            cout << endl;
        }
    } else
        cout << "No path found";
}
