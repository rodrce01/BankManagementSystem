#include "BankAccount.h"
#include <iostream>

int BankAccount::totalAccounts = 0;

BankAccount::BankAccount() : accountNumber(0), accountType("Checking"), balance(0.0) {
    totalAccounts++;
}

BankAccount::BankAccount(int number, const std::string &ty, double bal)
    : accountNumber(number), accountType(type), balance(bal) {
    totalAccounts++;
}

BankAccount::BankAccount(const BankAccount &other)
    : accountNumber(other.accountNumber), 
    accountType(other.accountType),
    balance(other.balance) {
    totalAccounts++;
}

int BankAccount::getAccountNumber() const { return accountNumber; }
std::string BankAccount:: getAccountType() const {return accountType;}
double BankAccount::getBalance() const {return balance;}

bool BankAccount::withdraw(double amount) {
    if (amount > balance) {
        std::cout << "Error: Insufficient funds.\n";
        return false;
    }
    balance -= amount;
    return true;
}

void BankAccount::deposit(double amount) {
    balance += amount;
}

void BankAccount::printAccountSummary() const {
    std::cout << "Account Number: " << accountNumber << accountNumber << "\n"
    << "Type: " << accountType << "\n"
    << "Balance: $" << balance << "\n";
}

int BankAccount::getTotalAccounts() {
    return totalAccounts;
}
