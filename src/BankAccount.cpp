#include "BankAccount.h"
#include <iostream>

int BankAccount::accountCount = 0;

BankAccount::BankAccount() : accountNumber(0), accountType("Checking"), balance(0.0) {
    accountCount++;
}
BankAccount::BankAccount(int accNum, const std::string& type, double bal)
    : accountNumber(accNum), accountType(type), balance(bal) {
    accountCount++;
}
BankAccount::BankAccount(const BankAccount& other)
    : accountNumber(other.accountNumber), accountType(other.accountType),
      balance(other.balance), transactionHistory(other.transactionHistory) {
    accountCount++;
}
BankAccount::~BankAccount() {
    accountCount--;
}

int BankAccount::getAccountNumber() const { return accountNumber; }
void BankAccount::setAccountNumber(int accNum) { accountNumber = accNum; }

std::string BankAccount::getAccountType() const { return accountType; }
void BankAccount::setAccountType(const std::string& type) { accountType = type; }

double BankAccount::getBalance() const { return balance; }
void BankAccount::setBalance(double bal) { balance = bal; }

void BankAccount::deposit(double amount) {
    balance += amount;
    transactionHistory.push_back("Deposited: " + std::to_string(amount));
}

bool BankAccount::withdraw(double amount) {
    if (amount > balance) {
        std::cout << "Error: Insufficient funds.\n";
        return false;
    }
    balance -= amount;
    transactionHistory.push_back("Withdrew: " + std::to_string(amount));
    return true;
}

void BankAccount::printAccountSummary() const {
    std::cout << "Account #" << accountNumber << " (" << accountType << ")\n";
    std::cout << "Balance: $" << balance << "\nTransactions:\n";
    for (const auto& t : transactionHistory) {
        std::cout << " - " << t << "\n";
    }
}

int BankAccount::getAccountCount() {
    return accountCount;
}