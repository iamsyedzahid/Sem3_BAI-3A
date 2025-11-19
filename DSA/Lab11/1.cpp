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

class HashTable {
private:
    static const int tableSize = 10;
    Node* arr[tableSize];

    int sumStr(const string& key) const {
        int sum = 0;
        int len = key.length();
        char c_arr[len + 1];
        strcpy(c_arr, key.c_str());
        for (int i = 0; i < len; i++) {
            sum += c_arr[i];
        }
        return sum;
    }

    int hashFunction(int sum) const {
        return sum % tableSize;
    }

public:
    HashTable() {
        for (int i = 0; i < tableSize; i++) {
            arr[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = arr[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            arr[i] = nullptr;
        }
    }
    
    void insert(const string& key, const string& value) {
        int hashIndex = hashFunction(sumStr(key));
        
        Node* current = arr[hashIndex];
        while (current != nullptr) {
            if (current->key == key) {
                cout << "Updating key '" << key << "' from '" << current->value << "' to '" << value << "'." << endl;
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(key, value);
        
        newNode->next = arr[hashIndex];
        arr[hashIndex] = newNode;

        cout << "Inserted/Updated: (" << key << ", " << value << ") at index " << hashIndex << endl;
    }
};

int main() {
    
    HashTable myhash;

    cout << "--- Insertion Operations ---" << endl;
    myhash.insert("A", "aaaaa");
    myhash.insert("B", "bbbbb");
    myhash.insert("C", "ccccc");
    return 0;
}
