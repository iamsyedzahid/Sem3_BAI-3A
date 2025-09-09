#include <iostream>
using namespace std;
int main() {
    int departments = 4;
    int courses[4] = {3,4,2,1};
    string deptNames[4] = {"SE","AI","CS","DS"};
    float** gpa = new float*[departments];
    for (int i = 0; i < departments; i++) gpa[i] = new float[courses[i]];
    for (int i = 0; i < departments; i++)
        for (int j = 0; j < courses[i]; j++) cin >> gpa[i][j];
    for (int i = 0; i < departments; i++) {
        cout << deptNames[i] << ": ";
        for (int j = 0; j < courses[i]; j++) cout << gpa[i][j] << " ";
        cout << endl;
    }
    for (int i = 0; i < departments; i++) delete[] gpa[i];
    delete[] gpa;
    return 0;
}
