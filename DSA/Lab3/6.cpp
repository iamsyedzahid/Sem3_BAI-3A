#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int v) { data = v; next = NULL; }
};

void append(Node*& head, int v) {
    Node* n = new Node(v);
    if (!head) { head = n; return; }
    Node* t=head; while(t->next) t=t->next; t->next=n;
}

void deleteValue(Node*& head, int val) {
    if (!head) return;
    Node* t = head;
    while (t->next && t->next->data != val) t = t->next;
    if (!t->next) { cout << "Value not found\n"; return; }
    Node* d = t->next;
    t->next = t->next->next;
    delete d;
}

void printList(Node* head) {
    while(head) { cout << head->data << " "; head=head->next; }
    cout << endl;
}

int main() {
    Node* head=NULL;
    for(int v: {1,2,3,4,5}) append(head,v);
    deleteValue(head,3);
    printList(head);
}
