#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

// ============================================================
// Helper: Get timestamp
// ============================================================
static std::string currentTime() {
    time_t now = time(0);
    tm lt;
    localtime_s(&lt, &now);

    char buffer[50];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &lt);
    return std::string(buffer);
}

// ============================================================
// Base Transaction Class
// ============================================================
class Transaction {
protected:
    double amount;
    std::string timestamp;

public:
    Transaction(double amt)
        : amount(amt), timestamp(currentTime()) {
    }

    virtual ~Transaction() = default;
    virtual std::string getType() const = 0;

    virtual std::string toString() const {
        char buffer[50];
        sprintf_s(buffer, "%.2f", amount);
        return timestamp + " | " + getType() + " | Amount: $" + buffer;
    }
};

// ============================================================
// Deposit Transaction
// ============================================================
class DepositTransaction : public Transaction {
public:
    DepositTransaction(double amt)
        : Transaction(amt) {
    }
    std::string getType() const override { return "DEPOSIT"; }
};

// ============================================================
// Withdraw Transaction
// ============================================================
class WithdrawTransaction : public Transaction {
public:
    WithdrawTransaction(double amt)
        : Transaction(amt) {
    }
    std::string getType() const override { return "WITHDRAW"; }
};

// ============================================================
// Logger
// ============================================================
class TransactionLogger {
private:
    std::string filename;

public:
    TransactionLogger(const std::string& file = "../data/transactionslog.txt")
        : filename(file) {
    }

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
