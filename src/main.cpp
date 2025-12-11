#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "User.h"
#include "BankAccount.h"
#include "Transaction.h"
#include "Manager.h"

using namespace std;

const int MAX_USERS = 200;

//load user transactions
void loadUserTransactions(const string& username, string history[], int &count, int max, const string &logFile) {
    ifstream fin(logFile);
    if (!fin.is_open()) {
        cerr << "ERROR: Could not open transaction log file.\n";
        count = 0;
        return;
    }
    count = 0;
    string line;
    while (getline(fin, line) && count < max) {
        if (line.rfind("[" + username + "]", 0) == 0) { 
            history[count] = line;
            count++;
        }
    }
    fin.close();
}

//save all users to file
void saveUsers(User users[], int userCount, const string &filename) {
    ofstream out(filename);
    if (out.is_open()) {
        for (int i = 0; i < userCount; i++)
            out << users[i].serialize() << "\n";
        out.close();
    } 
    else {
        cerr << "ERROR: Could not save users to file.\n";
    }
}

int main() {
    User users[MAX_USERS];
    int userCount = 0;

    Manager manager;
    TransactionLogger logger;

    //load managers
    manager.loadManagers("data/managers.txt");

    //load users
    ifstream userFile("data/users.txt");
    if (userFile.is_open()) {
        string line;
        while (getline(userFile, line) && userCount < MAX_USERS) {
            users[userCount] = User::deserialize(line);
            userCount++;
        }
        userFile.close();
    } 
    else {
        cout << "ERROR: Could not open users.txt!\n";
    }

    int choice;
    do {
        cout << "\nBANK MANAGEMENT SYSTEM\n";
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
                    if (users[i].getUsername() == username && users[i].getPassword() == password) {
                        currentUser = &users[i];
                        break;
                    }
                }

                if (currentUser != nullptr) {
                    cout << "Login successful! User: " << currentUser->getFullName() << ".\n";
                    int userChoice;
                    do {
                        cout << "\nUSER MENU\n";
                        cout << "1. Deposit\n";
                        cout << "2. Withdraw\n";
                        cout << "3. Print Account Summary\n";
                        cout << "4. View Transaction History\n";
                        cout << "5. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> userChoice;
                        cin.ignore();

                        switch(userChoice) {
                            case 1: {
                                double amt;
                                cout << "Enter amount to deposit: ";
                                cin >> amt; cin.ignore();
                                currentUser->getAccount().deposit(amt);
                                DepositTransaction t(amt);
                                logger.log(t, currentUser->getUsername());
                                cout << "Deposit successful!\n";
                                break;
                            }
                            case 2: {
                                double amt;
                                cout << "Enter amount to withdraw: ";
                                cin >> amt; cin.ignore();
                                if (currentUser->getAccount().withdraw(amt)) {
                                    WithdrawTransaction t(amt);
                                    logger.log(t, currentUser->getUsername());
                                    cout << "Withdrawal successful!\n";
                                } 
                                else {
                                    cout << "Insufficient funds.\n";
                                }
                                break;
                            }
                            case 3:
                                currentUser->getAccount().printAccountSummary();
                                break;
                            case 4: {
                                const int MAX_HISTORY = 200;
                                string history[MAX_HISTORY];
                                int count = 0;
                                loadUserTransactions(currentUser->getUsername(), history, count, MAX_HISTORY, "data/transactionslog.txt");
                                cout << "\nTRANSACTION HISTORY\n";
                                if (count == 0) {
                                    cout << "No transactions found.\n";
                                } 
                                else {
                                    for (int i = 0; i < count; i++)
                                        cout << history[i] << "\n";
                                }
                                break;
                            }
                            case 5:
                                cout << "Logging out!\n";
                                break;
                            default:
                                cout << "Must be number 1, 2, 3, 4, or 5.\n";
                        }

                    } while (userChoice != 5);

                    //save users on logout
                    saveUsers(users, userCount, "data/users.txt");
                } 
                else {
                    cout << "Login failed. Incorrect username or password.\n";
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
                cin >> accNum; cin.ignore();
                cout << "Enter account type: ";
                getline(cin, accType);
                cout << "Enter initial balance: ";
                cin >> balance; cin.ignore();

                BankAccount acc(accNum, accType, balance);
                users[userCount] = User(username, password, fullname, acc);
                userCount++;

                //append to file
                ofstream out("data/users.txt", ios::app);
                if (out.is_open()) {
                    out << users[userCount - 1].serialize() << "\n";
                    out.close();
                }

                cout << "Account created!\n";
                break;
            }

            case 3: {
                string username, password;
                cout << "Enter manager username: ";
                getline(cin, username);
                cout << "Enter manager password: ";
                getline(cin, password);

                if (manager.login(username, password)) {
                    cout << "Manager login successful!\n";
                    int managerChoice;
                    do {
                        cout << "\nMANAGER MENU\n";
                        cout << "1. List Users\n";
                        cout << "2. Delete User\n";
                        cout << "3. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> managerChoice;
                        cin.ignore();
                        switch(managerChoice) {
                            case 1:
                                cout << "LIST OF USERS\n";
                                for (int i = 0; i < userCount; i++) {
                                    cout << users[i].getUsername() << " | "
                                         << users[i].getFullName() << " | Balance: $"
                                         << users[i].getAccount().getBalance() << "\n";
                                }
                                break;

                            case 2: {
                                string delUser;
                                cout << "Enter username to delete: ";
                                getline(cin, delUser);

                                int index = -1;
                                for (int i = 0; i < userCount; i++) {
                                    if (users[i].getUsername() == delUser) {
                                        index = i;
                                        break;
                                    }
                                }

                                if (index != -1) {
                                    for (int j = index;j < userCount - 1; j++)
                                        users[j] = users[j + 1];
                                    userCount--;
                                    saveUsers(users, userCount, "data/users.txt");
                                    cout << "User " << delUser << " deleted.\n";
                                } 
                                else {
                                    cout << "User not found.\n";
                                }
                                break;
                            }

                            case 3:
                                cout << "Logging out!\n";
                                break;

                            default:
                                cout << "Must be number 1, 2, or 3.\n";
                        }

                    } while (managerChoice != 3);

                } 
                else {
                    cout << "Manager login failed. Incorrect username or password.\n";
                }
                break;
            }
            case 4:
                cout << "Exiting!\n";
                break;
            default:
                cout << "Must be number 1, 2, 3, or 4.\n";
        }
    } while (choice != 4);

    return 0;
}