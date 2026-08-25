# 🛒 KalaNet

**KalaNet** is a desktop-based marketplace application developed using **C++ and Qt**.

The application allows users to register and log in, create and manage product advertisements, browse available products, add items to a shopping cart, make purchases using a wallet, and view transaction history. An admin system is also included for reviewing, approving, or rejecting advertisements.

## ✨ Features

* 🔐 User registration and login
* 👤 User profile management
* 🛍️ Create and manage product advertisements
* 📋 Browse available advertisements
* 🏷️ Product categorization
* 👨‍💼 Admin advertisement management
* ✅ Approve advertisements
* ❌ Reject advertisements
* 🛒 Shopping cart
* 💰 Wallet management
* 💳 Checkout and payment
* 📜 Transaction history
* 🔒 Email and phone number validation
* 🔑 Password hashing
* 🧵 Thread-safe data management using `std::mutex`

## 🛠️ Tech Stack

* **C++17**
* **Qt**
* **Qt Widgets**
* **Qt Network**
* **CMake**
* **Object-Oriented Programming (OOP)**

The project uses C++17 and Qt modules such as `Widgets` and `Network`.

## 📂 Project Structure

```text
proj/
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
│
├── kalanetcore.cpp
├── kalanetcore.h
├── models.h
├── definitions.h
│
├── signupdialog.cpp
├── signupdialog.h
├── signupdialog.ui
│
├── logindialog.cpp
├── logindialog.h
├── logindialog.ui
│
├── homewindow.cpp
├── homewindow.h
├── homewindow.ui
│
├── addaddialog.cpp
├── addaddialog.h
├── addaddialog.ui
│
├── adwidget.cpp
├── adwidget.h
├── adwidget.ui
│
├── adviewerdialog.cpp
├── adviewerdialog.h
├── adviewerdialog.ui
│
├── walletdialog.cpp
├── walletdialog.h
├── walletdialog.ui
│
├── profiledialog.cpp
├── profiledialog.h
├── profiledialog.ui
│
└── CMakeLists.txt
```

## 🧩 Architecture

The main business logic of the application is handled by the `KalaNetCore` class.

It is responsible for managing:

* Users
* Advertisements
* Transactions
* Authentication
* User registration
* User profiles
* Advertisement creation
* Advertisement approval and rejection
* Shopping carts
* Payments
* Wallets
* Transaction history

The project also uses `std::mutex` to provide thread-safe access to shared data.

### Data Models

The main data models include:

#### User

A user contains information such as:

* Username
* Password hash
* Full name
* Phone number
* Email
* Wallet balance
* User role
* Shopping cart

#### Advertisement

Each advertisement contains:

* Advertisement ID
* Seller
* Title
* Description
* Price
* Category
* Image
* Advertisement status

Possible advertisement statuses include:

```text
PENDING
APPROVED
SOLD
```

#### Transaction

Each transaction stores information such as:

* Transaction ID
* Buyer
* Seller
* Advertisement ID
* Amount
* Date

## 👥 User Roles

KalaNet supports two main user roles:

```text
CUSTOMER
ADMIN
```

### Customer

Customers can:

* Browse advertisements
* Create advertisements
* Add products to their shopping cart
* Purchase products
* Manage their wallet
* View their transaction history
* Manage their profile

### Admin

Administrators can:

* Review advertisements
* Approve advertisements
* Reject advertisements
* Manage marketplace content

## 🏷️ Product Categories

Products are organized into the following categories:

* 🛋️ Furniture
* 💻 Electronics
* 👕 Clothing
* 📦 Other

## 🔄 Application Flow

```text
                    ┌──────────────┐
                    │    Start     │
                    └──────┬───────┘
                           │
                           ▼
                  ┌─────────────────┐
                  │ Login / Sign Up │
                  └────────┬────────┘
                           │
                           ▼
                    ┌─────────────┐
                    │ Home Window │
                    └──────┬──────┘
                           │
              ┌────────────┼────────────┐
              ▼            ▼            ▼
          View Ads      Post Ad      Profile
              │            │
              ▼            ▼
          Add to Cart   Admin Review
              │            │
              ▼            ▼
           Checkout   Approve / Reject
              │
              ▼
        Wallet Payment
              │
              ▼
         Transaction
```

## 🚀 Installation

### Prerequisites

Make sure you have the following installed:

* A C++ compiler with C++17 support
* CMake 3.16 or later
* Qt 5 or Qt 6
* Qt Widgets
* Qt Network

### Clone the Repository

```bash
git clone https://github.com/amirrezamoulaei/proj.git
cd proj
```

### Build the Project

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

After the build process finishes, run the generated executable.

> The exact executable path depends on your operating system, compiler, and Qt configuration.

## 🖥️ Build with Qt Creator

If you are using **Qt Creator**:

1. Clone the repository.
2. Open the project's `CMakeLists.txt` file.
3. Select a suitable Qt Kit.
4. Configure the project.
5. Build the project.
6. Run the application.

## 🔐 Error Handling

KalaNet uses custom exceptions to handle different types of errors:

```text
KalaNetException
├── AuthException
├── ValidationException
├── WalletException
└── AdException
```

This structure separates authentication, validation, wallet, and advertisement-related errors.

## 💰 Wallet & Transactions

Each user has a wallet with a specific balance.

The wallet system supports operations such as:

* Adding funds
* Checking the wallet balance
* Withdrawing funds
* Paying during checkout

After a successful purchase, transaction information is recorded, including the buyer, seller, product, amount, and transaction date.

## 🧪 Project Status

KalaNet is currently under development.

The project provides the core functionality required for a desktop marketplace, including user management, advertisements, shopping cart functionality, wallet management, transactions, and administrative controls.

## 🔮 Future Improvements

Potential improvements for future versions include:

* SQLite or PostgreSQL database integration
* Client-server architecture
* REST API
* Product search
* Advertisement filtering and sorting
* Product reviews and ratings
* Notification system
* Online payment integration
* Stronger encryption for sensitive information
* Unit and integration tests
* Improved UI/UX
* Better image and file management
* Docker support
* CI/CD pipeline

## 📄 License

No specific license has been added to the repository yet.

## 👨‍💻 Author

Developed by **Amir Reza Moulaei** & **Mohammad Erfan Izadi**

GitHub:
https://github.com/amirrezamoulaei

---

⭐ If you find this project useful, consider giving the repository a star!
