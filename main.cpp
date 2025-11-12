#include <iostream>
#include <vector>
#include "Account.h"
using namespace std;

vector<Account> accounts;

void createAccount() {
    string num, name;
    double bal;
    cout << "Enter Account Number: ";
    cin >> num;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Initial Balance: ";
    cin >> bal;
    accounts.push_back(Account(num, name, bal));
    cout << "Account created successfully!\n";
}

void findAccount(string num) {
    for (auto &acc : accounts) {
        if (acc.getAccountNumber() == num) {
            acc.display();
            return;
        }
    }
    cout << "Account not found!\n";
}

void showAll() {
    for (auto &a : accounts) {
        a.display();
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n=== Bank System Menu ===\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. View Account\n5. Show All\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            createAccount();
        else if (choice == 2) {
            string num;
            double amt;
            cout << "Enter Account Number: ";
            cin >> num;
            cout << "Enter Amount: ";
            cin >> amt;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == num) {
                    acc.deposit(amt);
                    goto done;
                }
            }
            cout << "Account not found!\n";
            done:;
        }
        else if (choice == 3) {
            string num;
            double amt;
            cout << "Enter Account Number: ";
            cin >> num;
            cout << "Enter Amount: ";
            cin >> amt;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == num) {
                    acc.withdraw(amt);
                    goto done2;
                }
            }
            cout << "Account not found!\n";
            done2:;
        }
        else if (choice == 4) {
            string num;
            cout << "Enter Account Number: ";
            cin >> num;
            findAccount(num);
        }
        else if (choice == 5) {
            showAll();
        }
        else if (choice == 6) break;
        else cout << "Invalid choice!\n";
    }
    return 0;
}
