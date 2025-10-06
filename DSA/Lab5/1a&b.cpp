//Q1.a.
#include <iostream>
struct Node {
int data;
Node* next;
Node(int val) : data(val), next(nullptr) {}
};
// Function to insert a node at the end (Iterative approach)
void insertAtEnd(Node*& head, int data) {
Node* newNode = new Node(data);
if (head == nullptr) {
head = newNode;
return;
}
Node* current = head;
while (current->next != nullptr) {
current = current->next;
}
current->next = newNode;
}
// Function to display the linked list in reverse order using Recursion
void displayReverse(Node* head) {
if (head == nullptr) {
return;
}
displayReverse(head->next);
std::cout << head->data << " ";
}

//====================================================================================================================================================================
//Q1.b.
#include <iostream>
struct DNode {
int data;
DNode* prev;
DNode* next;
DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};
// Function to display the doubly linked list
void displayList(DNode* head) {

DNode* current = head;
while (current != nullptr) {
std::cout << current->data << (current->next != nullptr ? " <-> " : "");
current = current->next;
}
std::cout << std::endl;
}
// Function to insert a node at a specified position (1-based index)
void insertAtPosition(DNode*& head, int data, int position) {
if (position < 1) return;
DNode* newNode = new DNode(data);
if (position == 1) {
newNode->next = head;
if (head != nullptr) head->prev = newNode;
head = newNode;
return;
}
DNode* current = head;
int count = 1;
while (current != nullptr && count < position - 1) {
current = current->next;
count++;
}
if (current == nullptr) {
delete newNode;
return;
}
newNode->next = current->next;
newNode->prev = current;
if (current->next != nullptr) {
current->next->prev = newNode;
}
current->next = newNode;
}
// Function to delete a node at a specified position (1-based index)
void deleteAtPosition(DNode*& head, int position) {
if (head == nullptr || position < 1) return;

DNode* current = head;
if (position == 1) {
head = head->next;
if (head != nullptr) head->prev = nullptr;
delete current;
return;
}
int count = 1;
while (current != nullptr && count < position) {
current = current->next;
count++;
}
if (current == nullptr) return;
if (current->prev != nullptr) {
current->prev->next = current->next;
}
if (current->next != nullptr) {
current->next->prev = current->prev;
}
delete current;
}
