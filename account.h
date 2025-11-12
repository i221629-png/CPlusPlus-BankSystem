#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <string>
using namespace std;

class Account {
private:
    string accountNumber;
    string name;
    double balance;
public:
    Account(string acc, string n, double b);
    void deposit(double amount);
    void withdraw(double amount);
    void display();
    string getAccountNumber();
    double getBalance();
};
#endif
