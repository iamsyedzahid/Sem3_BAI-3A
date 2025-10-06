#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) { data = d; next = NULL; }
};

int lengthTail(Node* head, int count = 0) {
    if (head == NULL) return count;
    return lengthTail(head->next, count + 1);
}

int main() {
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    cout << "Length: " << lengthTail(head);
}
