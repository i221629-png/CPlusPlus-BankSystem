#include <iostream>
}


int main() {
int choice;
while (true) {
cout << "\n=== Bank System Menu ===\n";
cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. View Account\n5. Show All\n6. Admin\n7. Exit\n";
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
goto done; // INTENTIONAL: use of goto (code smell)
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
goto done2; // INTENTIONAL: goto again
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
else if (choice == 6) {
adminAccess();
}
else if (choice == 7) break;
else cout << "Invalid choice!\n";
}
return 0;
}
