#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

std::string currentTime();

class Transaction {
protected:
    double amount;
    std::string timestamp;

public:
    Transaction(double amt);
    virtual ~Transaction() = default;

    virtual std::string getType() const = 0;

    virtual std::string toString() const;
};

class DepositTransaction : public Transaction {
public:
    DepositTransaction(double amt);
    std::string getType() const override;
};

class WithdrawTransaction : public Transaction {
public:
    WithdrawTransaction(double amt);
    std::string getType() const override;
};

class TransactionLogger {
private:
    std::string filename;

public:
    TransactionLogger(const std::string &file = "data/transactionslog.txt");

    void log(const Transaction &t, const std::string &user);
};

#endif

