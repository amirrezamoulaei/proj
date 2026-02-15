#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <ctime>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

enum class UserRole { CUSTOMER, ADMIN };

enum class AdStatus { PENDING, APPROVED, SOLD };

enum class Category { FURNITURE, ELECTRONICS, CLOTHING, OTHER };

class KalaNetException : public std::runtime_error
{
public:
    explicit KalaNetException(const std::string &msg)
        : std::runtime_error(msg)
    {}
};

class AuthException : public KalaNetException
{
public:
    explicit AuthException(const std::string &msg)
        : KalaNetException("Auth Error: " + msg)
    {}
};

class ValidationException : public KalaNetException
{
public:
    explicit ValidationException(const std::string &msg)
        : KalaNetException("Validation Error: " + msg)
    {}
};

class WalletException : public KalaNetException
{
public:
    explicit WalletException(const std::string &msg)
        : KalaNetException("Wallet Error: " + msg)
    {}
};

class AdException : public KalaNetException
{
public:
    explicit AdException(const std::string &msg)
        : KalaNetException("Ad/Cart Error: " + msg)
    {}
};

struct DateTime
{
    time_t rawTime;

    static std::string nowToString()
    {
        time_t now = time(0);
        char buf[80];
        struct tm tstruct;
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        return std::string(buf);
    }
};

#endif
