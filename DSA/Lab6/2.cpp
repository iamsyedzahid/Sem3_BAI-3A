#include <iostream>
using namespace std;

struct Node {
    string url;
    Node* next;
    Node(string u) : url(u), next(nullptr) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(string url) {
        Node* newNode = new Node(url);
        newNode->next = top;
        top = newNode;
    }

    string pop() {
        if (top == nullptr) {
            cout << "Stack Underflow" << endl;
            return "";
        }
        Node* temp = top;
        string url = top->url;
        top = top->next;
        delete temp;
        return url;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    ~Stack() {
        while (top != nullptr) {
            pop();
        }
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void add(string url) {
        Node* newNode = new Node(url);
        newNode->next = head;
        head = newNode;
    }

    void removeTwo() {
        if (head == nullptr) return;
        Node* temp1 = head;
        head = head->next;
        delete temp1;

        if (head == nullptr) return;
        Node* temp2 = head;
        head = head->next;
        delete temp2;
    }

    void print() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->url << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList history;
    Stack backStack;

    history.add("Instagram");
    backStack.push("Instagram");
    history.add("LinkedIn");
    backStack.push("LinkedIn");
    history.add("Twitter");
    backStack.push("Twitter");
    history.add("Facebook");
    backStack.push("Facebook");
    history.add("Google");
    backStack.push("Google");

    cout << "Browsing history: ";
    history.print();

    backStack.pop();
    backStack.pop();
    history.removeTwo();

    cout << "\nAfter going back two steps:\n";
    cout << "Browsing history: ";
    history.print();

    return 0;
}
