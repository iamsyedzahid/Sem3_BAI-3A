#include <iostream>
#include <cmath>
#include <stack>
using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

string infixToPostfix(string expression) {
    stack<char> s;
    string postfix = "";

    for (int i = 0; i < expression.length(); i++) {
        char current = expression[i];

        if (isalnum(current)) {
            postfix += current;
        }
        else if (current == '(') {
            s.push(current);
        }
        else if (current == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if (isOperator(current)) {
            while (!s.empty() && precedence(s.top()) >= precedence(current)) {
                postfix += s.top();
                s.pop();
            }
            s.push(current);
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

int main() {
    string infix = "a+b*(c^d-e)^(f+g*h)-i";
    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;
    return 0;
}
