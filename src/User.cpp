#include "User.h"
#include <sstream>

User::User() : username(""), password(""), fullName(""), account() {}

User::User(const std::string &u, const std::string &p, const std::string &name, const BankAccount &acc)
    : username(u), password(p), fullName(name), account(acc) {}

User::User(const User &other)
    : username(other.username), password(other.password), fullName(other.fullName), account(other.account) {}

std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getFullName() const { return fullName; }

void User::setPassword(const std::string &p) { password = p; }
void User::setFullName(const std::string &name) { fullName = name; }

BankAccount& User::getAccount() { return account; }

std::string User::serialize() const{
    std::ostringstream ss;
    ss << username << ","
        << password << ","
        << fullName << ","
        << account.getAccountNumber() << ","
        << account.getAccountType() << ","
        << account.getBalance();
    return ss.str();
}

User User::deserialize(const std::string &line) {
    std::stringstream ss(line);
    std::string u, p, name, accNumStr, type, balanceStr;

    getline(ss, u, ',');
    getline(ss, p, ',');
    getline(ss, name, ',');
    getline(ss, accNumStr, ',');
    getline(ss, type, ',');
    getline(ss, balanceStr, ',');

    BankAccount acc(std::stoi(accNumStr), type, std::stod(balanceStr));
    return User(u, p, name, acc);
}
