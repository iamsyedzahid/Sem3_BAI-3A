#include <iostream>
using namespace std;
int main() {
    int rows; cin >> rows;
    int* seats = new int[rows];
    string** chart = new string*[rows];
    for (int i = 0; i < rows; i++) {
        cin >> seats[i];
        chart[i] = new string[seats[i]];
        for (int j = 0; j < seats[i]; j++) cin >> chart[i][j];
    }
    for (int i = 0; i < rows; i++) {
        cout << "Row " << i+1 << ": ";
        for (int j = 0; j < seats[i]; j++) cout << chart[i][j] << " ";
        cout << endl;
    }
    for (int i = 0; i < rows; i++) delete[] chart[i];
    delete[] chart;
    delete[] seats;
    return 0;
}
