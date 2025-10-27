#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string name;
    int score;
    Node* next;

    Node(string n, int s) : name(n), score(s), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    void insert(string name, int score) {
        Node* newNode = new Node(name, score);
        newNode->next = head;
        head = newNode;
    }

    void display() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        Node* current = head;
        while (current != nullptr) {
            cout << "[Name: " << current->name << ", Score: " << current->score << "] -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }

    void radixSort() {
        int maxScore = 100; 

        for (int exp = 1; maxScore / exp > 0; exp *= 10) {
            
            Node* bucketHeads[10] = {nullptr};
            Node* bucketTails[10] = {nullptr};

            Node* current = head;
            while (current != nullptr) {
                int digit = (current->score / exp) % 10;
                
                Node* nextNode = current->next;
                
                current->next = nullptr; 

                if (bucketHeads[digit] == nullptr) {
                    bucketHeads[digit] = current;
                    bucketTails[digit] = current;
                } else {
                    bucketTails[digit]->next = current;
                    bucketTails[digit] = current; 
                }
                
                current = nextNode;
            }

            head = nullptr; 
            Node* tail = nullptr; 

            for (int i = 0; i < 10; i++) {
                if (bucketHeads[i] != nullptr) {
                    if (head == nullptr) {
                        head = bucketHeads[i];
                        tail = bucketTails[i];
                    } else {
                        tail->next = bucketHeads[i];
                        tail = bucketTails[i];
                    }
                }
            }
        }
    }

    bool findAndDelete(string name, int score) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->name == name && current->score == score) {
                
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                
                delete current; 
                cout << "\nRecord found and deleted." << endl;
                return true;
            }
            
            prev = current;
            current = current->next;
        }

        cout << "\nRecord not found." << endl;
        return false;
    }
};


int main() {
    LinkedList list;
    list.insert("Zahid", 78);
    list.insert("Saad", 95);
    list.insert("Ahmed", 100);
    
    cout << "Original List:" << endl;
    list.display();

    cout << "\nSorting list using Radix Sort: " << endl;
    list.radixSort();
    
    cout << "Sorted List:" << endl;
    list.display();

    string nameToFind;
    int scoreToFind;

    cout << "\nSearch and Delete" << endl;
    cout << "Enter student name to delete: ";
    getline(cin, nameToFind);
    
    cout << "Enter student score to delete: ";
    cin >> scoreToFind;
    cin.ignore(); 

    if (list.findAndDelete(nameToFind, scoreToFind)) {
        cout << "Updated List:" << endl;
        list.display();
    }

    cout << "\nSearch and Delete (Not Found Example)" << endl;
    cout << "Enter student name to delete: ";
    getline(cin, nameToFind);
    
    cout << "Enter student score to delete: ";
    cin >> scoreToFind;

    if (list.findAndDelete(nameToFind, scoreToFind)) {
        cout << "Updated List:" << endl;
        list.display();
    }

    return 0;
}
