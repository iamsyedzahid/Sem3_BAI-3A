#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    Node* next;
    Node(string n) { name = n; next = NULL; }
};

void insertSorted(Node*& head, string name) {
    Node* n = new Node(name);
    if (!head || name < head->name) {
        n->next = head;
        head = n;
        return;
    }
    Node* t = head;
    while (t->next && t->next->name < name) t = t->next;
    n->next = t->next;
    t->next = n;
}

void cancelReservation(Node*& head, string name) {
    if (!head) return;
    if (head->name == name) {
        Node* d = head;
        head = head->next;
        delete d;
        cout << "Reservation cancelled for " << name << endl;
        return;
    }
    Node* t = head;
    while (t->next && t->next->name != name) t = t->next;
    if (!t->next) cout << "No reservation found for " << name << endl;
    else {
        Node* d = t->next;
        t->next = t->next->next;
        delete d;
        cout << "Reservation cancelled for " << name << endl;
    }
}

bool checkReservation(Node* head, string name) {
    while (head) {
        if (head->name == name) return true;
        head = head->next;
    }
    return false;
}

void displayPassengers(Node* head) {
    if (!head) { cout << "No passengers reserved.\n"; return; }
    cout << "Passenger List:\n";
    while (head) {
        cout << head->name << endl;
        head = head->next;
    }
}

int main() {
    Node* head = NULL;
    int choice;
    string name;
    do {
        cout << "\n--- Airline Ticket Reservation Menu ---\n";
        cout << "1. Reserve Ticket\n";
        cout << "2. Cancel Reservation\n";
        cout << "3. Check Reservation\n";
        cout << "4. Display Passengers\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1:
                cout << "Enter passenger name: ";
                getline(cin, name);
                insertSorted(head, name);
                cout << "Ticket reserved for " << name << endl;
                break;
            case 2:
                cout << "Enter passenger name to cancel: ";
                getline(cin, name);
                cancelReservation(head, name);
                break;
            case 3:
                cout << "Enter passenger name to check: ";
                getline(cin, name);
                if (checkReservation(head, name)) 
                    cout << name << " has a reservation.\n";
                else 
                    cout << name << " does not have a reservation.\n";
                break;
            case 4:
                displayPassengers(head);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}
