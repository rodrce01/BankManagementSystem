#include "Transaction.h"
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
std::string currentTime() {

   time_t now = time(0);
    tm lt;

    #if defined(_WIN32) || defined(_WIN64)
        localtime_s(&lt, &now); //Windows
    #else
        localtime_r(&now, &lt); //Mac/Linux
    #endif

        char buffer[50];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &lt);
        return std::string(buffer);
}


