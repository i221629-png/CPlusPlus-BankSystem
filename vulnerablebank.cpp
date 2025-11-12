// VulnerableBank.cpp
// Deliberately insecure C++ sample for static analysis practice.
// Contains multiple common security issues (buffer overflows, command injection,
// hardcoded credentials, insecure randomness, use-after-free, temp-file race, etc.)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
  #include <stdlib.h>
#endif

using namespace std; // Poor practice in larger projects

class Account {
public:
    char accountNumber[20]; // fixed-size C buffer (overflow risk)
    char name[50];          // fixed-size C buffer (overflow risk)
    double balance;

    Account(const char* acc, const char* n, double b) {
        // INTENTIONAL: unsafe copy without bounds checking
        strcpy(accountNumber, acc); // possible buffer overflow
        strcpy(name, n);            // possible buffer overflow
        balance = b;
    }

    void deposit(double amount) {
        // INTENTIONAL: no checks for NaN/inf/overflow
        balance += amount;
        printf("Deposited %.2f. New balance: %.2f\n", amount, balance);
    }

    void withdraw(double amount) {
        // INTENTIONAL: removed proper balance checks -> negative balances allowed
        balance -= amount;
        printf("Withdrew %.2f. Remaining balance: %.2f\n", amount, balance);
    }

    void display() {
        // Information disclosure: prints account number and name directly
        printf("Account: %s, Name: %s, Balance: %.2f\n", accountNumber, name, balance);
    }
};

// Hardcoded credential (bad)
const char* ADMIN_PASSWORD = "P@ssw0rd123";

vector<Account*> accounts; // global mutable state (code smell)

void create_account() {
    char accNum[20];
    char custName[50];
    double bal;

    printf("Enter Account Number: ");
    // INTENTIONAL: using scanf %s without width limit -> buffer overflow
    scanf("%s", accNum);

    // consume newline leftover
    int c = getchar();
    while (c != '\n' && c != EOF) c = getchar();

    printf("Enter Name: ");
    // INTENTIONAL: read more characters than buffer (second parameter intentionally wrong)
    cin.getline(custName, 100); // custName is 50 bytes but reading up to 100 -> overflow

    printf("Enter Initial Balance: ");
    if (scanf("%lf", &bal) != 1) {
        printf("Invalid number, defaulting to 0\n");
        bal = 0.0;
    }

    // No validation of accNum or custName
    Account* a = new Account(accNum, custName, bal);
    accounts.push_back(a);
    printf("Account created.\n");
}

Account* find_account(const char* acc) {
    for (auto &a : accounts) {
        if (strcmp(a->accountNumber, acc) == 0) return a;
    }
    return nullptr;
}

void admin_console() {
    char input[64];
    printf("Enter admin password: ");
    // INTENTIONAL: reading password on console with printf/scanf (echoed) and using hardcoded password
    scanf("%63s", input);
    if (strcmp(input, ADMIN_PASSWORD) == 0) {
        printf("Admin granted. Showing all accounts:\n");
        for (auto &a : accounts) a->display();
    } else {
        printf("Access denied.\n");
    }
}

void unsafe_system_list() {
    char target[200];
    printf("Enter directory to list (unsafe - command injection demo): ");
    // INTENTIONAL: no bounds checking
    scanf("%s", target);

    // Build a command using strcat/strcpy - vulnerable to injection
    char cmd[256];
    strcpy(cmd, "ls ");    // on Windows this won't be ideal but kept for example
    strcat(cmd, target);   // no sanitization -> command injection
    // Using system() with user input is dangerous
    system(cmd);
}

void insecure_tmpfile_demo() {
    // INTENTIONAL: use tmpnam (race condition) then fopen -> TOCTOU
    char tmp[L_tmpnam];
    if (tmpnam(tmp) == nullptr) {
        printf("tmpnam failed\n");
        return;
    }
    printf("Temporary filename (insecure): %s\n", tmp);

    // Without O_EXCL or secure creation, attacker can race and create file first
    FILE* f = fopen(tmp, "w+");
    if (f) {
        fprintf(f, "Sensitive temp data\n");
        fclose(f);
        printf("Wrote insecure temp file.\n");
    } else {
        printf("Failed to open temp file.\n");
    }
}

void insecure_pin_generation() {
    // INTENTIONAL: using rand() seeded with time() for PIN generation (predictable)
    srand((unsigned)time(NULL));
    int pin = rand() % 10000; // 4-digit PIN, predictable
    printf("Generated insecure PIN: %04d\n", pin);
}

void use_after_free_demo() {
    // INTENTIONAL: use-after-free
    char* secret = new char[32];
    strcpy(secret, "VERY_SECRET_TOKEN");
    delete[] secret; // freed
    // still using pointer after free - undefined behaviour and exploit risk
    printf("Secret (use-after-free): %s\n", secret);
}

int main() {
    int choice = 0;
    while (1) {
        printf("\n--- Vulnerable Bank Menu ---\n");
        printf("1) Create Account\n2) Deposit\n3) Withdraw\n4) View Account\n5) Admin Console\n6) Unsafe ls (cmd inject)\n7) Insecure tempfile demo\n8) Insecure PIN gen\n9) Use-after-free demo\n10) Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            // clear input and continue
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }

        if (choice == 1) {
            create_account();
        } else if (choice == 2) {
            char acc[20];
            double amt;
            printf("Account number: ");
            scanf("%19s", acc);
            printf("Amount: ");
            scanf("%lf", &amt);
            Account* a = find_account(acc);
            if (a) {
                a->deposit(amt);
            } else printf("Not found\n");
        } else if (choice == 3) {
            char acc[20];
            double amt;
            printf("Account number: ");
            scanf("%19s", acc);
            printf("Amount: ");
            scanf("%lf", &amt);
            Account* a = find_account(acc);
            if (a) {
                a->withdraw(amt);
            } else printf("Not found\n");
        } else if (choice == 4) {
            char acc[20];
            printf("Account number: ");
            scanf("%19s", acc);
            Account* a = find_account(acc);
            if (a) a->display();
            else printf("Not found\n");
        } else if (choice == 5) {
            admin_console();
        } else if (choice == 6) {
            unsafe_system_list();
        } else if (choice == 7) {
            insecure_tmpfile_demo();
        } else if (choice == 8) {
            insecure_pin_generation();
        } else if (choice == 9) {
            use_after_free_demo();
        } else if (choice == 10) {
            // CLEANUP: intentionally not deleting allocated accounts to simulate memory leaks
            printf("Exiting (leaks and all)...\n");
            break;
        } else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
