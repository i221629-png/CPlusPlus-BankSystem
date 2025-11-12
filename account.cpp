#include "Account.h"

Account::Account(string acc, string n, double b) {
    accountNumber = acc;
    name = n;
    balance = b;
}

void Account::deposit(double amount) {
    if(amount <= 0) {
        cout << "Invalid deposit amount!\n";
        return;
    }
    balance += amount;
    cout << "Deposited " << amount << ". New balance: " << balance << endl;
}

void Account::withdraw(double amount) {
    if(amount > balance) {
        cout << "Insufficient funds!\n";
        return;
    }
    balance -= amount;
    cout << "Withdrew " << amount << ". Remaining balance: " << balance << endl;
}

void Account::display() {
    cout << "Account: " << accountNumber << ", Name: " << name 
         << ", Balance: " << balance << endl;
}

string Account::getAccountNumber() { return accountNumber; }
double Account::getBalance() { return balance; }
