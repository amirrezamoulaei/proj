#ifndef KALANETCORE_H
#define KALANETCORE_H

#include "Models.h"
#include <map>
#include <vector>
#include <string>
#include <mutex>

class KalaNetCore {
private:
    std::map<std::string, User*> users;
    std::map<std::string, Ad*> ads;
    std::vector<Transaction> transactions;

    User* currentUser;
    int adCounter = 1000;
    int transactionCounter = 5000;
    std::mutex dataMutex;

    std::string generateHash(const std::string& password);
    void validateEmail(const std::string& email); 
    void validatePhone(const std::string& phone);

public:
    KalaNetCore();
    ~KalaNetCore();

 
    void signup(std::string username, std::string password, 
                std::string name, std::string phone, std::string email);
    
    void login(std::string username, std::string password);
    void logout();
    User* getLoggedInUser();

    void postAd(std::string title, std::string desc, double price, 
                Category cat, std::string imagePath);
    
    std::vector<Ad*> getAvailableAds();
    std::vector<Ad*> getPendingAds();
    std::vector<Ad*> getMyAds();

 
    void approveAd(std::string adId);
    void rejectAd(std::string adId);

  
    void addToCart(std::string adId);
    std::vector<Ad*> getCartItems();
    double getCartTotal();
    
    
    void checkout(); 


    void chargeWallet(double amount);
    
    std::vector<Transaction> getUserHistory();
};

#endif
