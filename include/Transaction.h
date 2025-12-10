#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

// Helper function
std::string currentTime();

// ============================================================
// Base Transaction Class
// ============================================================
class Transaction {
protected:
    double amount;
    std::string timestamp;

public:
    Transaction(double amt) : amount(amt), timestamp(currentTime()) {}
    virtual ~Transaction() {}

    virtual std::string getType() const = 0;

    virtual std::string toString() const {
        std::ostringstream oss;
        oss << timestamp << " | " << getType() << " | Amount: $" << std::fixed << std::setprecision(2) << amount;
        return oss.str();
    }
};

// ============================================================
// Deposit Transaction
// ============================================================
class DepositTransaction : public Transaction {
public:
    DepositTransaction(double amt) : Transaction(amt) {}
    std::string getType() const override { return "DEPOSIT"; }
};

// ============================================================
// Withdraw Transaction
// ============================================================
class WithdrawTransaction : public Transaction {
public:
    WithdrawTransaction(double amt) : Transaction(amt) {}
    std::string getType() const override { return "WITHDRAW"; }
};

// ============================================================
// Transaction Logger
// ============================================================
class TransactionLogger {
private:
    std::string filename;

public:
    TransactionLogger(const std::string& file = "data/transactionslog.txt") : filename(file) {}

    void log(const Transaction& t, const std::string& user) {
        std::ofstream fout(filename, std::ios::app);
        if (!fout.is_open()) {
            std::cerr << "ERROR: Could not open log file.\n";
            return;
        }
        fout << "[" << user << "] " << t.toString() << "\n";
        fout.close();
    }
};

#endif


