#include <iostream>
#include <string>
using namespace std;

class MessageQueue {
private:
    struct Node {
        string message;
        int timestamp;
        Node* next;

        Node(string msg, int ts) : message(msg), timestamp(ts), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int size;

public:
    MessageQueue() : front(nullptr), rear(nullptr), size(0) {}

    void enqueue(string message, int timestamp) {
        Node* newNode = new Node(message, timestamp);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "No messages in the queue." << endl;
            return;
        }

        Node* temp = front;
        cout << "Processing message: " << front->message << endl;
        front = front->next;
        delete temp;
        size--;
    }

    void display() {
        if (front == nullptr) {
            cout << "Queue is empty!" << endl;
            return;
        }

        Node* temp = front;
        cout << "Messages in queue: ";
        while (temp != nullptr) {
            cout << temp->message << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    ~MessageQueue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main() {
    MessageQueue mq;

    mq.enqueue("Message 1: Hello!", 1);
    mq.enqueue("Message 2: How are you?", 2);
    mq.enqueue("Message 3: What's up?", 3);

    cout << "Messages in the queue before processing:" << endl;
    mq.display();

    mq.dequeue();
    mq.dequeue();

    cout << "\nMessages in the queue after processing:" << endl;
    mq.display();

    return 0;
}
