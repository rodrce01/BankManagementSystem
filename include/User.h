#ifndef USER_H
#define USER_H
#include <string>
#include "BankAccount.h"

class User {
private:
    std::string username;
    std::string password;
    std::string fullName;
    BankAccount account;

public:
    User();
    User(const std::string &u, const std::string &p, const std::string &name, const BankAccount &acc);
    User(const User &other);

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;

    void setPassword(const std::string &p);
    void setFullName(const std::string &name);

    BankAccount& getAccount();

    std::string serialize() const;
    static User deserialize(const std::string &line);
};
#endif
