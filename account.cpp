#include "Account.h"
#include <limits>


Account::Account(string acc, string n, double b) {
accountNumber = acc;
name = n;
balance = b;
}


void Account::deposit(double amount) {
// INTENTIONAL: no upper bound / overflow check
// A user could repeatedly deposit extremely large values to cause overflow.
if(amount <= 0) {
cout << "Invalid deposit amount!\n";
return;
}
// No saturation or range checking -> potential numeric issues
balance += amount;
cout << "Deposited " << amount << ". New balance: " << balance << endl;
}


void Account::withdraw(double amount) {
// INTENTIONAL: logic flaw - removed balance check to allow negative balances
// This demonstrates unchecked arithmetic / business logic vulnerability
// if(amount > balance) { cout << "Insufficient funds!\n"; return; }
balance -= amount; // can go negative
cout << "Withdrew " << amount << ". Remaining balance: " << balance << endl;
}


void Account::display() {
// Information disclosure: printing sensitive account number directly
cout << "Account: " << accountNumber << ", Name: " << name
<< ", Balance: " << balance << endl;
}


string Account::getAccountNumber() { return accountNumber; }
double Account::getBalance() { return balance; }
