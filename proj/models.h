#ifndef MODELS_H
#define MODELS_H

#include "Definitions.h"
#include <algorithm>
#include <iostream>

class Ad
{
private:
    std::string id;
    std::string sellerUsername;
    std::string title;
    std::string description;
    double price;
    Category category;
    std::string imagePath;
    AdStatus status;

public:
    Ad(std::string _id,
       std::string _seller,
       std::string _title,
       std::string _desc,
       double _price,
       Category _cat,
       std::string _img)
        : id(_id)
        , sellerUsername(_seller)
        , title(_title)
        , description(_desc)
        , price(_price)
        , category(_cat)
        , imagePath(_img)
        , status(AdStatus::APPROVED)
    {}

    std::string getId() const { return id; }
    std::string getSeller() const { return sellerUsername; }
    std::string getTitle() const { return title; }
    std::string getDescription() const {return description;}
    double getPrice() const { return price; }
    AdStatus getStatus() const { return status; }
    std::string getImagePath() const { return imagePath; }
    Category getCategory() const {return category;}

    void setStatus(AdStatus newStatus) { status = newStatus; }

    std::string getStatusString() const
    {
        switch (status) {
        case AdStatus::PENDING:
            return "Pending Approval";
        case AdStatus::APPROVED:
            return "Available";
        case AdStatus::SOLD:
            return "Sold";
        default:
            return "Unknown";
        }
    }
};

class Transaction
{
public:
    std::string id;
    std::string buyerUser;
    std::string sellerUser;
    std::string adId;
    double amount;
    std::string date;

    Transaction(
        std::string _id, std::string _buyer, std::string _seller, std::string _adId, double _amount)
        : id(_id)
        , buyerUser(_buyer)
        , sellerUser(_seller)
        , adId(_adId)
        , amount(_amount)
    {
        date = DateTime::nowToString();
    }
};

class User
{
protected:
    std::string username;
    std::string passwordHash;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    double walletBalance;
    UserRole role;

    std::vector<std::string> shoppingCart;

public:
    User(std::string _user,
         std::string _passHash,
         std::string _name,
         std::string _phone,
         std::string _email,
         UserRole _role = UserRole::CUSTOMER)
        : username(_user)
        , passwordHash(_passHash)
        , fullName(_name)
        , phoneNumber(_phone)
        , email(_email)
        , walletBalance(0.0)
        , role(_role)
    {}

    virtual ~User() {}

    std::string getUsername() const { return username; }
    bool checkPassword(const std::string &inputHash) const { return passwordHash == inputHash; }
    double getBalance() const { return walletBalance; }
    UserRole getRole() const { return role; }
    std::string getFullName() const { return fullName; }
    std::string getEmail() const {return email;}
    std::string getPass() const {return passwordHash;}
    std::string getPhone() const {return phoneNumber;}

    void setName(std::string name){ fullName = name;}
    void setUsername(std::string uname){ username = uname;}
    void setPassword(std::string pass){ passwordHash = pass;}
    void setPhone(std::string phone){ phoneNumber = phone;}
    void setEmail(std::string semail){ email = semail;}

    void deposit(double amount)
    {
        if (amount > 0)
            walletBalance += amount;
    }

    bool withdraw(double amount)
    {
        if (walletBalance >= amount) {
            walletBalance -= amount;
            return true;
        }
        return false;
    }

    void addToCart(const std::string &adId)
    {
        if (std::find(shoppingCart.begin(), shoppingCart.end(), adId) == shoppingCart.end()) {
            shoppingCart.push_back(adId);
        }
    }

    void removeFromCart(const std::string &adId)
    {
        shoppingCart.erase(std::remove(shoppingCart.begin(), shoppingCart.end(), adId),
                           shoppingCart.end());
    }

    void clearCart() { shoppingCart.clear(); }

    const std::vector<std::string> &getCart() const { return shoppingCart; }
};

#endif
