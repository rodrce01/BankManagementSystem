#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>

class BankAccount {
private:
    int accountNumber;
    std::string accountType;
    double balance;
    std::vector<std::string> transactionHistory;

    static int accountCount; 

public:
    BankAccount();  
    BankAccount(int accNum, const std::string& type, double bal);
    BankAccount(const BankAccount& other);

    ~BankAccount();

    int getAccountNumber() const;
    void setAccountNumber(int accNum);

    std::string getAccountType() const;
    void setAccountType(const std::string& type);

    double getBalance() const;
    void setBalance(double bal);

    void deposit(double amount);
    bool withdraw(double amount);
    void printAccountSummary() const;

    static int getAccountCount();
};

#endif