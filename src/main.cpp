#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "User.h"
#include "BankAccount.h"
#include "Transaction.h"
#include "Manager.h"

using namespace std;

int main() {
    vector<User> users;
    Manager manager;
    TransactionLogger logger;

    //load managers
    manager.loadManagers("data/managers.txt");

    //load users from file
    ifstream userFile("data/users.txt");
    if (userFile.is_open()) {
        string line;
        while (getline(userFile, line)) {
            users.push_back(User::deserialize(line));
        }
        userFile.close();
    } else {
        cout << "ERROR: Could not open users.txt!!!!\n";
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

                bool loggedIn = false;
                User *currentUser = nullptr;

                //check credentials
                for (auto &u : users) {
                    if (u.getUsername() == username && u.getPassword() == password) {
                        loggedIn = true;
                        currentUser = &u;
                        break;
                    }
                }

                if (loggedIn) {
                    cout << "Login successful! Welcome, " << currentUser->getFullName() << ".\n";

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

                                //log transaction
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

                                if(currentUser->getAccount().withdraw(amt)) {
                                    //log transaction
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
                                cout << "Logging out...\n";
                                break;
                            default:
                                cout << "Invalid choice.\n";
                        }

                    } while(userChoice != 4);

                    //save updated user info back to file
                    ofstream out("data/users.txt");
                    if(out.is_open()) {
                        for(const auto &u : users) {
                            out << u.serialize() << "\n";
                        }
                        out.close();
                    }

                } else {
                    cout << "Login failed. Invalid username or password.\n";
                }

                break;
            }

            case 2: {
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

                BankAccount newAcc(accNum, accType, balance);
                User newUser(username, password, fullname, newAcc);
                users.push_back(newUser);

                //save to file
                ofstream out("data/users.txt", ios::app);
                if(out.is_open()) {
                    out << newUser.serialize() << "\n";
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

                if(manager.login(username, password)) {
                    cout << "Login successful! Welcome, " << username << ".\n";
                    cout << "--- LIST OF USERS ---\n";
                    for(const auto &u : users) {
                        cout << u.getUsername() << " | " << u.getFullName() << " | Balance: $"
                             << u.getAccount().getBalance() << "\n";
                    }
                } else {
                    cout << "Login failed. Invalid credentials.\n";
                }
                break;
            }

            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while(choice != 4);

    return 0;
}
