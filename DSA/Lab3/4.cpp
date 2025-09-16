#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int v) { data = v; next = NULL; }
};

void printList(Node* head) {
    while (head) { cout << head->data << " "; head = head->next; }
    cout << endl;
}

void append(Node*& head, int v) {
    Node* n = new Node(v);
    if (!head) { head = n; return; }
    Node* t = head; while (t->next) t = t->next;
    t->next = n;
}

Node* evenOdd(Node* head) {
    if (!head) return head;
    Node *evenStart=NULL, *evenEnd=NULL, *oddStart=NULL, *oddEnd=NULL;
    while (head) {
        if (head->data % 2 == 0) {
            if (!evenStart) evenStart = evenEnd = head;
            else { evenEnd->next = head; evenEnd = head; }
        } else {
            if (!oddStart) oddStart = oddEnd = head;
            else { oddEnd->next = head; oddEnd = head; }
        }
        head = head->next;
    }
    if (!evenStart || !oddStart) return (evenStart?evenStart:oddStart);
    evenEnd->next = oddStart;
    oddEnd->next = NULL;
    return evenStart;
}

int main() {
    int arr[] = {17,15,8,12,10,5,4,1,7,6};
    Node* head = NULL;
    for (int v: arr) append(head, v);
    head = evenOdd(head);
    printList(head);
}
