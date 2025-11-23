#include <iostream>
#include <string>

enum SlotStatus {
    EMPTY,      
    OCCUPIED,   
    DELETED     
};

struct Student {
    int rollNumber;
    std::string name;
    SlotStatus status;
};

class StudentHashTable {
private:
    static const int TABLE_SIZE = 15;
    Student table[TABLE_SIZE]; 

    int hashFunction(int rollNumber) const {
        return rollNumber % TABLE_SIZE;
    }

    int probe(int initialIndex, int attempt) const {
        return (initialIndex + attempt * attempt) % TABLE_SIZE;
    }

public:
    StudentHashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i].rollNumber = -1; 
            table[i].name = "";
            table[i].status = EMPTY;
        }
    }

    void InsertRecord(int rollNumber, const std::string& name) {
        int initialIndex = hashFunction(rollNumber);
        int attempt = 0;

        while (attempt < TABLE_SIZE) {
            int index = probe(initialIndex, attempt);

            if (table[index].status == EMPTY || table[index].status == DELETED) {
                table[index].rollNumber = rollNumber;
                table[index].name = name;
                table[index].status = OCCUPIED;
                std::cout << "Inserted: Roll " << rollNumber << ", Name " << name 
                          << " at index " << index << std::endl;
                return;
            }

            if (table[index].status == OCCUPIED && table[index].rollNumber == rollNumber) {
                std::cout << "Error: Roll " << rollNumber << " already exists." << std::endl;
                return;
            }

            attempt++;
        }

        std::cout << "Error: Hash table is full or insertion failed for Roll " << rollNumber << std::endl;
    }

    void SearchRecord(int rollNumber) const {
        int initialIndex = hashFunction(rollNumber);
        int attempt = 0;

        while (attempt < TABLE_SIZE) {
            int index = probe(initialIndex, attempt);

            if (table[index].status == OCCUPIED && table[index].rollNumber == rollNumber) {
                std::cout << "Record found: Roll " << rollNumber << ", Name: " 
                          << table[index].name << " at index " << index << std::endl;
                return;
            }

            if (table[index].status == EMPTY) {
                std::cout << "Record not found for Roll " << rollNumber << std::endl;
                return;
            }
            
            attempt++;
        }

        std::cout << "Record not found for Roll " << rollNumber << std::endl;
    }
    
    void DisplayTable() const {
        std::cout << "\n--- Student Hash Table (Quadratic Probing) ---" << std::endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "Slot " << i << ": ";
            if (table[i].status == OCCUPIED) {
                std::cout << "Roll " << table[i].rollNumber << " (" << table[i].name << ")";
            } else if (table[i].status == DELETED) {
                 std::cout << "DELETED";
            } else {
                std::cout << "EMPTY";
            }
            std::cout << std::endl;
        }
    }
};
