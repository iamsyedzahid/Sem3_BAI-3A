#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) { data = d; next = NULL; }
};

bool searchNonTail(Node* head, int key) {
    if (head == NULL) return false;
    if (searchNonTail(head->next, key)) return true;
    return head->data == key;
}

int main() {
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    int key = 20;
    cout << (searchNonTail(head, key) ? "Found" : "Not Found");
}
