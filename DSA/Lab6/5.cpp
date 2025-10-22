#include <iostream>
using namespace std;

class Queue {
private:
    int* arr;
    int front, rear, size, capacity;

public:
    Queue(int cap) : capacity(cap), front(0), rear(0), size(0) {
        arr = new int[capacity];
    }

    void enqueue(int customerID) {
        if (size == capacity) {
            cout << "Queue is full!" << endl;
        } else {
            arr[rear] = customerID;
            rear = (rear + 1) % capacity;
            size++;
        }
    }

    void dequeue() {
        if (size == 0) {
            cout << "Queue is empty!" << endl;
        } else {
            cout << "Customer " << arr[front] << " is being served." << endl;
            front = (front + 1) % capacity;
            size--;
        }
    }

    void display() {
        if (size == 0) {
            cout << "Queue is empty!" << endl;
        } else {
            cout << "Customers in queue: ";
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
    Queue q(7);

    q.enqueue(13);
    q.enqueue(7);
    q.enqueue(4);
    q.enqueue(1);
    q.enqueue(6);
    q.enqueue(8);
    q.enqueue(10);

    q.display();

    q.dequeue();
    q.dequeue();

    q.display();

    return 0;
}
