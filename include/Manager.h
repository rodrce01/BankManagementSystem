#ifndef MANAGER_H
#define MANAGER_H

#include <string>

class Manager {
private:
    static const int MAX_MANAGERS = 50;
    std::string usernames[MAX_MANAGERS];
    std::string passwords[MAX_MANAGERS];
    int managerCount;

public:
    Manager();

    void loadManagers(const std::string &filename);
    bool login(const std::string &username, const std::string &password) const;
};

#endif

