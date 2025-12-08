#ifndef USER_H
#define USER_H

#include <string>
#include "BankAccount.h"

class User {
private:
    std::string username;
    std::string password;
    BankAccount account;

public:
    User();  
    User(const std::string& uname, const std::string& pwd, const BankAccount& acc);
    User(const User& other);

    std::string getUsername() const;
    void setUsername(const std::string& uname);

    std::string getPassword() const;
    void setPassword(const std::string& pwd);

    BankAccount& getAccount();

    static User loadFromFile(const std::string& line);
    std::string saveToFile() const;

    bool verifyLogin(const std::string& uname, const std::string& pwd) const;
};

#endif