#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

void printList(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

void insertAtFront(Node*& head, int val) {
    Node* n = new Node(val);
    n->next = head;
    head = n;
}

void insertAtEnd(Node*& head, int val) {
    Node* n = new Node(val);
    if (!head) { head = n; return; }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = n;
}

void insertAtPos(Node*& head, int val, int pos) {
    if (pos == 1) { insertAtFront(head, val); return; }
    Node* temp = head;
    for (int i = 1; temp && i < pos - 1; i++) temp = temp->next;
    if (!temp) return;
    Node* n = new Node(val);
    n->next = temp->next;
    temp->next = n;
}

void deleteValue(Node*& head, int val) {
    if (!head) return;
    if (head->data == val) { Node* d = head; head = head->next; delete d; return; }
    Node* temp = head;
    while (temp->next && temp->next->data != val) temp = temp->next;
    if (temp->next) {
        Node* d = temp->next;
        temp->next = temp->next->next;
        delete d;
    }
}

int main() {
    int arr[] = {3, 1, 2, 5, 8};
    int n = 5;
    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    Node* head = NULL;
    for (int i = 0; i < n; i++) insertAtEnd(head, arr[i]);
    insertAtEnd(head, 9);
    insertAtPos(head, 11, 3);
    insertAtFront(head, 4);
    deleteValue(head, 1);
    deleteValue(head, 2);
    deleteValue(head, 5);
    cout << "Final Linked List: ";
    printList(head);
}
