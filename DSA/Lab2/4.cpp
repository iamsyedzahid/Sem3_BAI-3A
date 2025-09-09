#include <iostream>
using namespace std;
const int SIZE = 5;
bool hasCommonFriend(bool friends[SIZE][SIZE], int p1, int p2) {
    for (int k = 0; k < SIZE; k++) {
        if (k != p1 && k != p2 && friends[p1][k] && friends[p2][k]) return true;
    }
    return false;
}
int main() {
    bool friends[SIZE][SIZE] = {
        {0,1,0,1,1},
        {1,0,1,0,1},
        {0,1,0,0,0},
        {1,0,0,0,1},
        {1,1,0,1,0}
    };
    cout << hasCommonFriend(friends,0,4) << endl;
    cout << hasCommonFriend(friends,1,2) << endl;
    return 0;
}
