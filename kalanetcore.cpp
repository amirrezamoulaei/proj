#include "KalaNetCore.h"
#include <regex>
#include <algorithm>
#include <functional>

KalaNetCore::KalaNetCore() : currentUser(nullptr) {
    // default admin
    std::string adminUser = "admin";
    std::string adminPassHash = generateHash("admin123");
    users[adminUser] = new User(adminUser, adminPassHash, "System Admin", 
                                "09120000000", "admin@kalanet.com", UserRole::ADMIN);
}

KalaNetCore::~KalaNetCore() {
    for (auto const& [key, val] : users) delete val;
    for (auto const& [key, val] : ads) delete val;
    users.clear();
    ads.clear();
}


std::string KalaNetCore::generateHash(const std::string& password) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

void KalaNetCore::validateEmail(const std::string& email) {
    const std::regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.{1}\w+)+)");
    if (!std::regex_match(email, pattern)) {
        throw ValidationException("Invalid email format.");
    }
}

void KalaNetCore::validatePhone(const std::string& phone) {
    if (phone.length() != 11 || phone.substr(0, 2) != "09" || 
        !std::all_of(phone.begin(), phone.end(), ::isdigit)) {
        throw ValidationException("Invalid phone number (must start with 09 and be 11 digits).");
    }
}


void KalaNetCore::signup(std::string username, std::string password, 
                         std::string name, std::string phone, std::string email) {
    std::lock_guard<std::mutex> lock(dataMutex);

    if (users.find(username) != users.end()) {
        throw AuthException("Username already exists.");
    }
    if (password.length() < 8) {
        throw ValidationException("Password must be at least 8 characters.");
    }
    
    validateEmail(email);
    validatePhone(phone);

    std::string passHash = generateHash(password);
    users[username] = new User(username, passHash, name, phone, email, UserRole::CUSTOMER);
}

void KalaNetCore::login(std::string username, std::string password) {
    std::lock_guard<std::mutex> lock(dataMutex);

    auto it = users.find(username);
    if (it == users.end()) {
        throw AuthException("User not found.");
    }
    
    std::string inputHash = generateHash(password);
    if (!it->second->checkPassword(inputHash)) {
        throw AuthException("Incorrect password.");
    }
    
    currentUser = it->second;
}

void KalaNetCore::logout() {
    currentUser = nullptr;
}

User* KalaNetCore::getLoggedInUser() {
    return currentUser;
}


void KalaNetCore::postAd(std::string title, std::string desc, double price, 
                         Category cat, std::string imagePath) {
    if (!currentUser) throw AuthException("You must be logged in to post an ad.");
    if (price < 0) throw ValidationException("Price cannot be negative.");

    std::lock_guard<std::mutex> lock(dataMutex);
    
    std::string id = std::to_string(adCounter++);
    Ad* newAd = new Ad(id, currentUser->getUsername(), title, desc, price, cat, imagePath);
    ads[id] = newAd;
}

std::vector<Ad*> KalaNetCore::getAvailableAds() {
    std::vector<Ad*> result;
    for (auto const& [id, ad] : ads) {
        if (ad->getStatus() == AdStatus::APPROVED) {
            result.push_back(ad);
        }
    }
    return result;
}

std::vector<Ad*> KalaNetCore::getPendingAds() {
    std::vector<Ad*> result;
    if (!currentUser || currentUser->getRole() != UserRole::ADMIN) return result;
    
    for (auto const& [id, ad] : ads) {
        if (ad->getStatus() == AdStatus::PENDING) {
            result.push_back(ad);
        }
    }
    return result;
}

std::vector<Ad*> KalaNetCore::getMyAds() {
    std::vector<Ad*> result;
    if (!currentUser) return result;

    for (auto const& [id, ad] : ads) {
        if (ad->getSeller() == currentUser->getUsername()) {
            result.push_back(ad);
        }
    }
    return result;
}


void KalaNetCore::approveAd(std::string adId) {
    if (!currentUser || currentUser->getRole() != UserRole::ADMIN) 
        throw AuthException("Access denied. Admin only.");
    
    std::lock_guard<std::mutex> lock(dataMutex);
    
    if (ads.find(adId) == ads.end()) throw AdException("Ad ID not found.");
    ads[adId]->setStatus(AdStatus::APPROVED);
}

void KalaNetCore::rejectAd(std::string adId) {
    if (!currentUser || currentUser->getRole() != UserRole::ADMIN) 
        throw AuthException("Access denied. Admin only.");

    std::lock_guard<std::mutex> lock(dataMutex);
    
    auto it = ads.find(adId);
    if (it == ads.end()) throw AdException("Ad ID not found.");
    
    delete it->second;
    ads.erase(it);
}


void KalaNetCore::addToCart(std::string adId) {
    if (!currentUser) throw AuthException("Login required to shop.");
    
    std::lock_guard<std::mutex> lock(dataMutex);

    auto it = ads.find(adId);
    if (it == ads.end()) throw AdException("Ad not found.");
    
    Ad* ad = it->second;

    if (ad->getStatus() != AdStatus::APPROVED) {
        throw AdException("Item is not available (Sold or Pending).");
    }
    if (ad->getSeller() == currentUser->getUsername()) {
        throw AdException("You cannot buy your own item.");
    }

    currentUser->addToCart(adId);
}

std::vector<Ad*> KalaNetCore::getCartItems() {
    std::vector<Ad*> items;
    if (!currentUser) return items;

    const std::vector<std::string>& cartIds = currentUser->getCart();
    for (const std::string& id : cartIds) {
        if(ads.count(id)) items.push_back(ads[id]);
    }
    return items;
}

double KalaNetCore::getCartTotal() {
    double total = 0.0;
    std::vector<Ad*> items = getCartItems();
    for (Ad* ad : items) {
        total += ad->getPrice();
    }
    return total;
}

void KalaNetCore::checkout() {
    if (!currentUser) throw AuthException("Login required.");
    
    std::lock_guard<std::mutex> lock(dataMutex);

    std::vector<Ad*> items = getCartItems();
    if (items.empty()) throw AdException("Cart is empty.");

    double total = 0.0;
    
    for (Ad* ad : items) {
        if (ad->getStatus() != AdStatus::APPROVED) {
            throw AdException("Item '" + ad->getTitle() + "' is no longer available.");
        }
        total += ad->getPrice();
    }

    if (currentUser->getBalance() < total) {
        throw WalletException("Insufficient funds. Needed: " + std::to_string(total));
    }

    currentUser->withdraw(total);

    for (Ad* ad : items) {
        std::string sellerName = ad->getSeller();
        if (users.count(sellerName)) {
            users[sellerName]->deposit(ad->getPrice());
        }

        ad->setStatus(AdStatus::SOLD);

        std::string tId = std::to_string(transactionCounter++);
        Transaction t(tId, currentUser->getUsername(), sellerName, ad->getId(), ad->getPrice());
        transactions.push_back(t);
    }

    currentUser->clearCart();
}


void KalaNetCore::chargeWallet(double amount) {
    if (!currentUser) throw AuthException("Login required.");
    if (amount <= 0) throw ValidationException("Amount must be positive.");

    std::lock_guard<std::mutex> lock(dataMutex);
    currentUser->deposit(amount);
}

std::vector<Transaction> KalaNetCore::getUserHistory() {
    std::vector<Transaction> result;
    if (!currentUser) return result;

    for (const auto& t : transactions) {
        if (t.buyerUser == currentUser->getUsername() || t.sellerUser == currentUser->getUsername()) {
            result.push_back(t);
        }
    }
    return result;
}
