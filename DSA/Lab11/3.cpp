#include <iostream>

struct Node {
    int key;
    Node* next;

    Node(int k) : key(k), next(nullptr) {}
};

class CustomHashTable {
private:
    const int TABLE_SIZE;
    Node** table; 

    int hashFunction(int key) const {
        return key % TABLE_SIZE;
    }

public:
    CustomHashTable(int size) : TABLE_SIZE(size) {
        table = new Node*[TABLE_SIZE](); 
    }

    ~CustomHashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }

    void insert(int key) {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                std::cout << "Key " << key << " already exists." << std::endl;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(key);
        newNode->next = table[index];
        table[index] = newNode;
        std::cout << "Inserted key: " << key << std::endl;
    }

    void deleteKey(int key) {
        int index = hashFunction(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                std::cout << "Deleted key: " << key << std::endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        std::cout << "Key " << key << " not found for deletion." << std::endl;
    }

    bool search(int key) const {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                std::cout << "Search found key: " << key << " at index " << index << std::endl;
                return true;
            }
            current = current->next;
        }
        std::cout << "Search failed for key: " << key << std::endl;
        return false;
    }

    void display() const {
        std::cout << "\n Hash Table Contents " << std::endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "Bucket " << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                std::cout << current->key << " -> ";
                current = current->next;
            }
            std::cout << "NULL" << std::endl;
        }
        std::cout << "\n" << std::endl;
    }
};
