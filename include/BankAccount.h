#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>

class BankAccount {
private:
    int accountNumber;
    std::string accountType;
    double balance;

    static int totalAccounts; 

public:
    BankAccount();  
    BankAccount(int number, const std::string &type, double bal);
    BankAccount(const BankAccount &other);

    int getAccountNumber() const;
    std::string getAccountType() const;
    double getBalance() const;

    void setAccountType(const std::string &type);

    bool withdraw(double amount);
    void deposit(double amount);
    void printAccountSummary() const;

    static int getTotalAccounts();
};

#endif
