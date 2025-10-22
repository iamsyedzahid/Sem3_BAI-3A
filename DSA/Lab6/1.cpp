#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;
    int top;
    int capacity;

public:
    Stack(int size) {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }

    void push(int value) {
        if (top == capacity - 1) {
            cout << "Stack Overflow" << endl;
        } else {
            arr[++top] = value;
            cout << "Added " << value << " to the stack." << endl;
        }
    }

    bool isEmpty() {
        return top == -1;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        } else {
            return arr[top--];
        }
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        } else {
            return arr[top];
        }
    }

    ~Stack() {
        delete[] arr;
    }
};

int main() {
    Stack zahid(5);

    zahid.push(10);
    zahid.push(20);
    zahid.push(30);

    cout << "Top of the stack: " << zahid.peek() << endl;

    cout << "Removing top item: " << zahid.pop() << endl;

    if (zahid.isEmpty()) {
        cout << "Stack is empty!" << endl;
    } else {
        cout << "Stack is not empty!" << endl;
    }

    return 0;
}
