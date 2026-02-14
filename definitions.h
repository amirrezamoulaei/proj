#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>
#include <vector>
#include <ctime>
#include <sstream>

enum class UserRole {
    CUSTOMER,
    ADMIN
};

enum class AdStatus {
    PENDING,    
    APPROVED,  
    SOLD       
};


enum class Category {
    FURNITURE,
    ELECTRONICS,
    CLOTHING,
    OTHER
};


struct DateTime {
    time_t rawTime;
    
    static std::string nowToString() {
        time_t now = time(0);
        char buf[80];
        struct tm tstruct;
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        return std::string(buf);
    }
};

#endif 
