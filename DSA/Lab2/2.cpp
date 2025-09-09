#include <iostream>
using namespace std;
int main() {
    int students = 5, subjects = 4;
    int** marks = new int*[students];
    for (int i = 0; i < students; i++) marks[i] = new int[subjects];
    for (int i = 0; i < students; i++)
        for (int j = 0; j < subjects; j++) cin >> marks[i][j];
    int topper = 0, highestTotal = 0;
    for (int i = 0; i < students; i++) {
        int total = 0;
        for (int j = 0; j < subjects; j++) total += marks[i][j];
        cout << "Total of Student " << i+1 << ": " << total << endl;
        if (total > highestTotal) { highestTotal = total; topper = i; }
    }
    for (int j = 0; j < subjects; j++) {
        int sum = 0;
        for (int i = 0; i < students; i++) sum += marks[i][j];
        cout << "Average of Subject " << j+1 << ": " << sum / (float)students << endl;
    }
    cout << "Topper: Student " << topper+1 << endl;
    for (int i = 0; i < students; i++) delete[] marks[i];
    delete[] marks;
    return 0;
}
