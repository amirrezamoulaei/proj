#ifndef KALANETCORE_H
#define KALANETCORE_H

#include "Models.h"
#include <map>
#include <vector>
#include <string>
#include <mutex>

class KalaNetCore {
private:
    std::map<std::string, User*> users; // Key: username
    std::map<std::string, Ad*> ads;     // Key: adId
    std::vector<Transaction> transactions;

    User* currentUser; 

   
    int adCounter = 1000;
    int transactionCounter = 5000;

    std::mutex dataMutex;

    std::string generateHash(const std::string& password);
    bool validateEmail(const std::string& email);
    bool validatePhone(const std::string& phone);

public:
    KalaNetCore();
    ~KalaNetCore();

    std::string signup(std::string username, std::string password, 
                       std::string name, std::string phone, std::string email);
    
    bool login(std::string username, std::string password);
    void logout();
    User* getLoggedInUser();

    std::string postAd(std::string title, std::string desc, double price, 
                       Category cat, std::string imagePath);
    
    std::vector<Ad*> getAvailableAds(); 
    std::vector<Ad*> getPendingAds();   
    std::vector<Ad*> getMyAds();        

    bool approveAd(std::string adId);
    bool rejectAd(std::string adId);

    std::string addToCart(std::string adId);
    std::vector<Ad*> getCartItems();
    double getCartTotal();
    
    std::string checkout(); 

    void chargeWallet(double amount);
    
    std::vector<Transaction> getUserHistory();
};

#endif 
