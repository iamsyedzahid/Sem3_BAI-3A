#include <iostream>
using namespace std;
int main() {
    int departments; cin >> departments;
    int* students = new int[departments];
    int*** marks = new int**[departments];
    for (int i = 0; i < departments; i++) {
        cin >> students[i];
        marks[i] = new int*[students[i]];
        for (int j = 0; j < students[i]; j++) {
            marks[i][j] = new int[5];
            for (int k = 0; k < 5; k++) cin >> marks[i][j][k];
        }
    }
    for (int i = 0; i < departments; i++) {
        int total = 0, count = 0, highest = 0, lowest = 100;
        for (int j = 0; j < students[i]; j++) {
            for (int k = 0; k < 5; k++) {
                int m = marks[i][j][k];
                total += m; count++;
                if (m > highest) highest = m;
                if (m < lowest) lowest = m;
            }
        }
        cout << "Department " << i+1 << " -> Highest: " << highest << " Lowest: " << lowest << " Average: " << (float)total/count << endl;
    }
    for (int i = 0; i < departments; i++) {
        for (int j = 0; j < students[i]; j++) delete[] marks[i][j];
        delete[] marks[i];
    }
    delete[] marks;
    delete[] students;
    return 0;
}
