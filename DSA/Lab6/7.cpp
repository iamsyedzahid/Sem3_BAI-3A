#include <iostream>
using namespace std;

class Queue {
private:
    string* arr;
    int front, rear, size, capacity;

public:
    Queue(int cap) : capacity(cap), front(0), rear(0), size(0) {
        arr = new string[capacity];
    }

    void enqueue(string patron) {
        if (size == capacity) {
            cout << "Queue is full!" << endl;
        } else {
            arr[rear] = patron;
            rear = (rear + 1) % capacity;
            size++;
        }
    }

    void dequeue() {
        if (size == 0) {
            cout << "Queue is empty!" << endl;
        } else {
            cout << "Patron " << arr[front] << " has completed their transaction." << endl;
            front = (front + 1) % capacity;
            size--;
        }
    }

    void display() {
        if (size == 0) {
            cout << "Queue is empty!" << endl;
        } else {
            cout << "Patrons in queue: ";
            for (int i = 0; i < size; i++) {
                cout << arr[(front + i) % capacity] << " ";
            }
            cout << endl;
        }
    }

    ~Queue() {
        delete[] arr;
    }
};

int main() {
    Queue q(5);

    q.enqueue("John");
    q.enqueue("Alice");
    q.enqueue("Bob");

    q.display();

    q.dequeue();
    q.dequeue();

    q.display();

    return 0;
}
