#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) { data = val; next = NULL; }
};

void printList(Node* head) {
    while (head) { cout << head->data << " "; head = head->next; }
    cout << endl;
}

void append(Node*& head, int val) {
    Node* n = new Node(val);
    if (!head) { head = n; return; }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = n;
}

void rotate(Node*& head, int k) {
    if (!head || k == 0) return;
    Node* temp = head;
    int len = 1;
    while (temp->next) { temp = temp->next; len++; }
    temp->next = head;
    k %= len;
    for (int i = 0; i < k; i++) head = head->next;
    Node* newTail = head;
    for (int i = 1; i < len; i++) newTail = newTail->next;
    newTail->next = NULL;
}

int main() {
    int arr[] = {5, 3, 1, 8, 6, 4, 2};
    int n = 7;
    Node* head = NULL;
    for (int i = 0; i < n; i++) append(head, arr[i]);
    int k;
    cout << "Enter k: "; cin >> k;
    rotate(head, k);
    printList(head);
}
