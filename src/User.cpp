#include "User.h"
#include <sstream>

User::User() : username(""), password(""), account() {}

User::User(const std::string& uname, const std::string& pwd, const BankAccount& acc)
    : username(uname), password(pwd), account(acc) {}

User::User(const User& other)
    : username(other.username), password(other.password), account(other.account) {}

std::string User::getUsername() const { return username; }
void User::setUsername(const std::string& uname) { username = uname; }

std::string User::getPassword() const { return password; }
void User::setPassword(const std::string& pwd) { password = pwd; }

BankAccount& User::getAccount() { return account; }

bool User::verifyLogin(const std::string& uname, const std::string& pwd) const {
    return (username == uname && password == pwd);
}

User User::loadFromFile(const std::string& line) {
    std::stringstream ss(line);
    std::string uname, pwd, type;
    int accNum;
    double bal;
    ss >> uname >> pwd >> accNum >> type >> bal;
    BankAccount acc(accNum, type, bal);
    return User(uname, pwd, acc);
}

std::string User::saveToFile() const {
    std::stringstream ss;
    ss << username << " " << password << " "
       << account.getAccountNumber() << " "
       << account.getAccountType() << " "
       << account.getBalance();
    return ss.str();
}