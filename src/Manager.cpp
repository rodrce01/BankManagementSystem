#include "Manager.h"
#include <fstream>
#include <iostream>
#include <sstream>

Manager::Manager() {
    // Optionally, you can load managers here by default
    // loadManagers("data/managers.txt");
}

void Manager::loadManagers(const std::string &filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return;
    }

    managerList.clear();
    std::string line;

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string username, password;

        if (std::getline(ss, username, ',') && std::getline(ss, password)) {
            managerList.push_back({username, password});
        }
    }

    fin.close();
}

bool Manager::login(const std::string &username, const std::string &password) const {
    for (const auto &entry : managerList) {
        if (entry.first == username && entry.second == password) {
            return true; // login successful
        }
    }
    return false;
}

