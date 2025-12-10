#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <vector>
#include <utility>

class Manager {
private:
    std::vector<std::pair<std::string, std::string>> managerList;

public:
    Manager();

    void loadManagers(const std::string &filename);
    bool login(const std::string &username, const std::string &password) const;

};

#endif
