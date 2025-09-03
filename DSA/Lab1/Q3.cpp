#include <iostream>
using namespace std;

class Box {
private:
    int* value;

public:
    Box(int v) {
        value = new int;
        *value = v;
    }

    ~Box() {
        delete value;
    }

    Box(const Box& other) {
        value = new int;
        *value = *(other.value);
    }

    Box& operator=(const Box& other) {
        if (this != &other) {
            delete value;
            value = new int;
            *value = *(other.value);
        }
        return *this;
    }

    void display() const {
        cout << "Value: " << *value << endl;
    }
};

int main() {
    Box box1(10);
    cout << "Box 1: ";
    box1.display();

    Box box2 = box1;
    cout << "Box 2 (shallow copy of Box 1): ";
    box2.display();

    box2 = box1;
    cout << "Box 2 (after assignment from Box 1): ";
    box2.display();

    box1 = Box(20);
    cout << "Box 1 (modified): ";
    box1.display();

    cout << "Box 2 (after Box 1 is modified): ";
    box2.display();

    return 0;
}
