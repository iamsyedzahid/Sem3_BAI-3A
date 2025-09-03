#include <iostream>
using namespace std;

class BankAccount {
public:
    double acc_balance;

    BankAccount() {
        acc_balance = 0;
    }

    BankAccount(double initial_acc_balance) {
        acc_balance = initial_acc_balance;
    }

    BankAccount(const BankAccount& other) {
        acc_balance = other.acc_balance;
    }

    double get_acc_balance() {
        return acc_balance;
    }

    void deposit(double amount) {
        acc_balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= acc_balance) {
            acc_balance -= amount;
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }
};

int main() {
    BankAccount Saad;  
    cout << "Balance of Saad: $" << Saad.get_acc_balance() << endl;

    BankAccount Hanzala(1000);  
    cout << "Balance of Hanzala: $" << Hanzala.get_acc_balance() << endl;

    BankAccount Azan = Hanzala;  
    Azan.withdraw(200);
    cout << "Balance of Azan: $" << Azan.get_acc_balance() << endl;

    cout << "Balance of Hanzala: $" << Hanzala.get_acc_balance() << endl;

    return 0;
}
