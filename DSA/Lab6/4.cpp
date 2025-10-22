#include <iostream>
#include <stack>
#include <string>
using namespace std;

float evaluateExpression(string expression) {
    stack<float> s;

    for (int i = 0; i < expression.length(); i++) {
        char current = expression[i];

        if (isdigit(current)) {
            s.push(current - '0');
        } else if (current == '+') {
            float operand2 = s.top();
            s.pop();
            float operand1 = s.top();
            s.pop();
            s.push(operand1 + operand2);
        } else if (current == '-') {
            float operand2 = s.top();
            s.pop();
            float operand1 = s.top();
            s.pop();
            s.push(operand1 - operand2);
        } else if (current == '*') {
            float operand2 = s.top();
            s.pop();
            float operand1 = s.top();
            s.pop();
            s.push(operand1 * operand2);
        } else if (current == '/') {
            float operand2 = s.top();
            s.pop();
            float operand1 = s.top();
            s.pop();
            s.push(operand1 / operand2);
        }
    }

    return s.top();
}

int main() {
    string expression = "12+13-5*(0.5+0.5)+1";
    float result = evaluateExpression(expression);
    cout << "Result of the expression: " << result << endl;
    return 0;
}
