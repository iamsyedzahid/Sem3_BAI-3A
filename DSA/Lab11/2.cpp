#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Node {
    string key;
    string value;
    Node* next;

    Node(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

class Dictionary {
private:
    static const int tableSize = 100;
    Node* arr[tableSize];

    int calculate_ASCII_Sum(const string& key) const {
        int sum = 0;
        int len = key.length();
        char c_arr[len + 1]; 
        strcpy(c_arr, key.c_str()); 
        for (int i = 0; i < len; i++) {
            sum += c_arr[i];
        }
        return sum;
    }

    int hashFunction(const string& key) const {
        int sum = calculate_ASCII_Sum(key);
        return sum % tableSize;
    }

public:
    Dictionary() {
        for (int i = 0; i < tableSize; i++) {
            arr[i] = nullptr;
        }
    }

    ~Dictionary() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = arr[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    }

    void addRecord(const string& key, const string& value) {
        int hashIndex = hashFunction(key);
        
        Node* current = arr[hashIndex];
        while (current != nullptr) {
            if (current->key == key) {
                cout << "Record updated for key " << key << "." << endl;
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(key, value);
        newNode->next = arr[hashIndex];
        arr[hashIndex] = newNode;

        cout << "Added record (" << key << ", " << value << ") at index " << hashIndex << endl;
    }

    string wordSearch(const string& key) const {
        int hashIndex = hashFunction(key);
        
        Node* current = arr[hashIndex];
        
        while (current != nullptr) {
            if (current->key == key) {
                cout << "search key " << key << ": " << current->value << endl;
                return current->value;
            }
            current = current->next;
        }
        
        cout << "Error: Key '" << key << "' not found in the dictionary." << endl;
        return "";
    }
    
    bool deleteRecord(const string& key) {
        int hashIndex = hashFunction(key);
        Node* current = arr[hashIndex];
        Node* previous = nullptr;

        while (current != nullptr && current->key != key) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            return false;
        }
        
        if (previous == nullptr) {
            arr[hashIndex] = current->next;
        } else {
            previous->next = current->next;
        }
        
        delete current;
        cout << "key " << key << " deleted successfully !" << endl;
        return true;
    }

    void printDictionary() const {
        cout << "\n Complete Dictionary Contents (Table Size: " << tableSize << ") " << endl;
        for (int i = 0; i < tableSize; i++) {
            Node* current = arr[i];
            if (current != nullptr) {
                cout << "index " << i << ": ";
                while (current != nullptr) {
                    cout << "(" << current->key << ", " << current->value << ")";
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
                cout << endl;
            }
        }
    }
};

int main() {
    Dictionary myDictionary;

    myDictionary.addRecord("AB", "FASTNU");
    myDictionary.addRecord("CD", "CS");
    myDictionary.addRecord("EF", "ENGG"); 
  
    myDictionary.wordSearch("AB");
    myDictionary.wordSearch("ZX");

    myDictionary.deleteRecord("EF"); 

    myDictionary.printDictionary();

    return 0;
}
