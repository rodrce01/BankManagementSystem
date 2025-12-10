#include "Manager.h"
#include <fstream>
#include <iostream>
#include <sstream>

Manager::Manager() : managerCount(0) {}

void Manager::loadManagers(const std::string &filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return;
    }

    managerCount = 0;
    std::string line;

    while (std::getline(fin, line) && managerCount < MAX_MANAGERS) {
        std::stringstream ss(line);
        std::string username, password;

        if (std::getline(ss, username, ',') && std::getline(ss, password)) {
            usernames[managerCount] = username;
            passwords[managerCount] = password;
            managerCount++;
        }
    }

    fin.close();
}

bool Manager::login(const std::string &username, const std::string &password) const {
    for (int i = 0; i < managerCount; i++) {
        if (usernames[i] == username && passwords[i] == password)
            return true;
    }
    return false;
}
