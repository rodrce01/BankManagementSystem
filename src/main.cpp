#include <iostream>
#include <string>
#include <vector>

#include "User.h"
#include "BankAccount.h"
#include "Transaction.h"
#include "Manager.h"

using namespace std;

int main() {
    vector<User> users;
    Manager manager;
    TransactionLogger logger;

    manager.loadManagers("data/managers.txt");


    int choice;

    do {
        cout << "\n=== BANK MANAGEMENT SYSTEM ===\n";
        cout << "1. User Login\n";
        cout << "2. Create Account\n";
        cout << "3. Manager Login\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                // TODO: Call user login function from Person 1
                cout << "[User Login] - Not implemented yet.\n";
                break;
            }
            case 2: {
                // TODO: Call create account function from Person 1
                cout << "[Create Account] - Not implemented yet.\n";
                break;
            }
            case 3: {
                string username, password;
                cout << "Enter manager username: ";
                getline(cin, username);
                cout << "Enter manager password: ";
                getline(cin, password);

                if(manager.login(username, password)) {
                    cout << "Login successful! Welcome, " << username << ".\n";

                    // TODO: Optionally show all users or other manager functions
                    // Example: for(const auto &u : users) { ... }
                } else {
                    cout << "Login failed. Invalid credentials.\n";
                }
                break;
            }
            case 4: {
                cout << "Exiting program. Goodbye!\n";
                break;
            }
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while(choice != 4);

    return 0;
}
