#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

void insertNode(Node** head_ref, int new_data) {
    Node* new_node = new Node(new_data);
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void printList(Node* node) {
    while (node != nullptr) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

Node* getTail(Node* node) {
    while (node != nullptr && node->next != nullptr) {
        node = node->next;
    }
    return node;
}

void swapNodes(Node* a, Node* b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

Node* partition(Node* head, Node* tail) {
    int pivotData = tail->data;
    Node* i = head;

    for (Node* j = head; j != tail; j = j->next) {
        if (j->data < pivotData) {
            swapNodes(i, j);
            i = i->next;
        }
    }
    swapNodes(i, tail);
    return i;
}

void quickSortRec(Node* head, Node* tail) {
    if (head == nullptr || tail == nullptr || head == tail || head == tail->next) {
        return;
    }

    Node* pivot = partition(head, tail);

    Node* prev_pivot = head;
    if (head == pivot) {
        prev_pivot = nullptr;
    } else {
        while (prev_pivot != nullptr && prev_pivot->next != pivot) {
            prev_pivot = prev_pivot->next;
        }
    }

    quickSortRec(head, prev_pivot);
    quickSortRec(pivot->next, tail);
}

void quickSort(Node** head_ref) {
    Node* head = *head_ref;
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    Node* tail = getTail(head);
    quickSortRec(head, tail);
}

int main() {
    Node* head = nullptr;

    insertNode(&head, 3);
    insertNode(&head, 5);
    insertNode(&head, 1);
    insertNode(&head, 9);
    insertNode(&head, 8);
    insertNode(&head, 7);
    insertNode(&head, 10);

    cout << "Original List: ";
    printList(head);

    quickSort(&head);

    cout << "Sorted List: ";
    printList(head);

    return 0;
}
