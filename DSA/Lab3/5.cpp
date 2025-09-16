#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* next;
    Node(char v) { data = v; next = NULL; }
};

void append(Node*& head, char v) {
    Node* n = new Node(v);
    if (!head) { head = n; return; }
    Node* t = head; while (t->next) t = t->next;
    t->next = n;
}

Node* reverse(Node* head) {
    Node* prev = NULL;
    Node* curr = head;
    while (curr) {
        Node* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    return prev;
}

bool isPalindrome(Node* head) {
    if (!head || !head->next) return true;
    Node* slow = head;
    Node* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* secondHalf = reverse(slow->next);
    Node* p1 = head;
    Node* p2 = secondHalf;
    bool result = true;
    while (p2) {
        if (p1->data != p2->data) {
            result = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    slow->next = reverse(secondHalf);
    return result;
}

int main() {
    Node* head = NULL;
    string s = "BORROWORROB";
    for (char c: s) append(head, c);
    if (isPalindrome(head)) cout << "Linked List is a Palindrome\n";
    else cout << "Not a Palindrome\n";
}
