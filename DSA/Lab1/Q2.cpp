#include <iostream>
#include <string>
using namespace std;

class Exam {
private:
    string student_name;
    string exam_date;
    double* score;

public:
    Exam(const string& name, const string& date, double s) {
        student_name = name;
        exam_date = date;
        score = new double;
        *score = s;
    }

    void display_exam_details() {
        cout << "Student Name: " << student_name << endl;
        cout << "Exam Date: " << exam_date << endl;
        cout << "Score: " << *score << endl;
    }

    ~Exam() {
        delete score;
    }
};

int main() {
    Exam exam1("Zahid", "2025-09-03", 85.5);
    cout << "Details of exam1:" << endl;
    exam1.display_exam_details();

    Exam exam2 = exam1;
    cout << "\nDetails of exam2 (shallow copy of exam1):" << endl;
    exam2.display_exam_details();

    return 0;
}
