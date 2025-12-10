#include <iostream>
#include <string>
#include <fstream>

#include "User.h"
#include "BankAccount.h"
#include "Transaction.h"
#include "Manager.h"

using namespace std;

const int MAX_USERS = 200;

int main() {
    User users[MAX_USERS];
    int userCount = 0;

    Manager manager;
    TransactionLogger logger;

    manager.loadManagers("data/managers.txt");

    // load users
    ifstream userFile("data/users.txt");
    if (userFile.is_open()) {
        string line;
        while (getline(userFile, line) && userCount < MAX_USERS) {
            users[userCount] = User::deserialize(line);
            userCount++;
        }
        userFile.close();
    } else {
        cout << "ERROR: Could not open users.txt!\n";
    }

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
                string username, password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);

                User* currentUser = nullptr;

                for (int i = 0; i < userCount; i++) {
                    if (users[i].getUsername() == username &&
                        users[i].getPassword() == password) {
                        currentUser = &users[i];
                        break;
                    }
                }

                if (currentUser != nullptr) {
                    cout << "Login successful! Welcome, "
                         << currentUser->getFullName() << ".\n";

                    int userChoice;
                    do {
                        cout << "\n--- USER MENU ---\n";
                        cout << "1. Deposit\n";
                        cout << "2. Withdraw\n";
                        cout << "3. Print Account Summary\n";
                        cout << "4. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> userChoice;
                        cin.ignore();

                        switch(userChoice) {
                            case 1: {
                                double amt;
                                cout << "Enter amount to deposit: ";
                                cin >> amt;
                                cin.ignore();

                                currentUser->getAccount().deposit(amt);
                                DepositTransaction t(amt);
                                logger.log(t, currentUser->getUsername());
                                cout << "Deposit successful!\n";
                                break;
                            }

                            case 2: {
                                double amt;
                                cout << "Enter amount to withdraw: ";
                                cin >> amt;
                                cin.ignore();

                                if (currentUser->getAccount().withdraw(amt)) {
                                    WithdrawTransaction t(amt);
                                    logger.log(t, currentUser->getUsername());
                                    cout << "Withdrawal successful!\n";
                                } else {
                                    cout << "Insufficient funds.\n";
                                }
                                break;
                            }

                            case 3:
                                currentUser->getAccount().printAccountSummary();
                                break;

                            case 4:
                                cout << "Logging out!\n";
                                break;

                            default:
                                cout << "Invalid choice.\n";
                        }

                    } while (userChoice != 4);

                    //save users on logout
                    ofstream out("data/users.txt");
                    if (out.is_open()) {
                        for (int i = 0; i < userCount; i++)
                            out << users[i].serialize() << "\n";
                        out.close();
                    }

                } else {
                    cout << "Login failed.\n";
                }

                break;
            }

            case 2: {
                if (userCount >= MAX_USERS) {
                    cout << "ERROR: User limit reached.\n";
                    break;
                }

                string username, password, fullname;
                int accNum;
                string accType;
                double balance;

                cout << "Enter new username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                cout << "Enter full name: ";
                getline(cin, fullname);
                cout << "Enter account number: ";
                cin >> accNum;
                cin.ignore();
                cout << "Enter account type: ";
                getline(cin, accType);
                cout << "Enter initial balance: ";
                cin >> balance;
                cin.ignore();

                BankAccount acc(accNum, accType, balance);
                users[userCount] = User(username, password, fullname, acc);
                userCount++;

                //append to file
                ofstream out("data/users.txt", ios::app);
                if (out.is_open()) {
                    out << users[userCount - 1].serialize() << "\n";
                    out.close();
                }

                cout << "Account created successfully!\n";
                break;
            }

            case 3: {
                string username, password;
                cout << "Enter manager username: ";
                getline(cin, username);
                cout << "Enter manager password: ";
                getline(cin, password);

                if (manager.login(username, password)) {
                    cout << "Login successful!\n";
                    cout << "--- LIST OF USERS ---\n";

                    for (int i = 0; i < userCount; i++) {
                        cout << users[i].getUsername() << " | "
                             << users[i].getFullName() << " | Balance: $"
                             << users[i].getAccount().getBalance() << "\n";
                    }

                } else {
                    cout << "Manager login failed.\n";
                }
                break;
            }

            case 4:
                cout << "Exiting!\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}

