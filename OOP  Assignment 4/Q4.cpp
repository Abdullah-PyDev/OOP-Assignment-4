#include<iostream>
#include<cstring>
using namespace std;

class UserProfile {
private:
    char* username;
    char* email;
    int userId;

public:
    UserProfile() : username(nullptr), email(nullptr), userId(0) {}

    UserProfile(const char* uname, const char* email, int uId) {
        username = new char[strlen(uname) + 1];
        strcpy_s(username, strlen(uname) + 1, uname);

        this->email = new char[strlen(email) + 1];
        strcpy_s(this->email, strlen(email) + 1, email);

        userId = uId;
    }

    // Disable copy
    UserProfile(const UserProfile&) = delete;
    UserProfile& operator=(const UserProfile&) = delete;

    void displayProfile() const {
        cout << "Username : " << (username ? username : "NULL") << endl;
        cout << "Email : " << (email ? email : "NULL") << endl;
        cout << "User ID : " << userId << endl;
    }

    ~UserProfile() {
        cout << "User Profile [" << (username ? username : "NULL") << "] deleted\n";
        delete[] username;
        delete[] email;
    }
};

class SecurityModule {
private:
    char* hashedPin;
    int failedAttempts;
    bool isLocked;

public:
    SecurityModule(const char* hPin) {
        isLocked = false;
        failedAttempts = 0;

        hashedPin = new char[strlen(hPin) + 1];
        strcpy_s(hashedPin, strlen(hPin) + 1, hPin);
    }

    // Disable copy
    SecurityModule(const SecurityModule&) = delete;
    SecurityModule& operator=(const SecurityModule&) = delete;

    bool authenticate(const char* pin) {
        if (isLocked) {
            cout << "Account is locked!\n";
            return false;
        }

        if (strcmp(pin, hashedPin) == 0) {
            failedAttempts = 0;
            return true;
        }
        else {
            failedAttempts++;
            cout << "Incorrect PIN\n";

            if (failedAttempts >= 3) {
                isLocked = true;
                cout << "Account locked after 3 failed attempts!\n";
            }
            return false;
        }
    }

    void resetLock() {
        isLocked = false;
        failedAttempts = 0;
    }

    ~SecurityModule() {
        cout << "Security Module removed\n";
        delete[] hashedPin;
    }
};

class PlatformAccount : public UserProfile, public SecurityModule {
private:
    char* accountType;
    double balance;
    int transactionLimit;

public:
    PlatformAccount(const char* uname, const char* email, int uId,
        const char* hPin, const char* accType,
        double bal, int transLimit)
        : UserProfile(uname, email, uId), SecurityModule(hPin) {

        accountType = new char[strlen(accType) + 1];
        strcpy_s(accountType, strlen(accType) + 1, accType);

        balance = bal;
        transactionLimit = transLimit;
    }

    // Disable copy
    PlatformAccount(const PlatformAccount&) = delete;
    PlatformAccount& operator=(const PlatformAccount&) = delete;

    bool deposit(double amount) {
        if (amount > transactionLimit) {
            cout << "Transaction limit exceeded\n";
            return false;
        }
        balance += amount;
        return true;
    }

    bool withdraw(double amount) {
        if (amount > transactionLimit) {
            cout << "Transaction limit exceeded\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance\n";
            return false;
        }
        balance -= amount;
        return true;
    }

    void displayAccountDetails() const {
        displayProfile();
        cout << "Account Type : " << (accountType ? accountType : "NULL") << endl;
        cout << "Balance : $" << balance << endl;
        cout << "Transaction Limit : $" << transactionLimit << endl;
    }

    ~PlatformAccount() {
        cout << "Platform Account [" << (accountType ? accountType : "NULL") << "] deleted\n";
        delete[] accountType;
    }
};

class PremiumAccount : public PlatformAccount {
private:
    char* vipCode;
    double cashbackRate;

public:
    PremiumAccount(const char* uname, const char* email, int uId,
        const char* hPin, const char* accType,
        double bal, int transLimit,
        const char* vipCode, double cashbackRate)
        : PlatformAccount(uname, email, uId, hPin, accType, bal, transLimit) {

        this->vipCode = new char[strlen(vipCode) + 1];
        strcpy_s(this->vipCode, strlen(vipCode) + 1, vipCode);
        this->cashbackRate = cashbackRate;
    }

    // Disable copy
    PremiumAccount(const PremiumAccount&) = delete;
    PremiumAccount& operator=(const PremiumAccount&) = delete;

    void displayPremiumDetails() const {
        displayAccountDetails();
        cout << "VIP Code : " << (vipCode ? vipCode : "NULL") << endl;
        cout << "Cashback Rate : " << cashbackRate << "%\n";
    }

    double calculateCashback(double spentAmount) const {
        return spentAmount * (cashbackRate / 100);
    }

    ~PremiumAccount() {
        cout << "Premium Account [" << (vipCode ? vipCode : "NULL") << "] deleted\n";
        delete[] vipCode;
    }
};

class DashboardConfig {
private:
    char* theme;
    bool notificationsEnabled;
    int refreshIntervalSeconds;

public:
    DashboardConfig(const char* theme, bool notificationsEnabled, int refreshInterval) {
        this->theme = new char[strlen(theme) + 1];
        strcpy_s(this->theme, strlen(theme) + 1, theme);
        this->notificationsEnabled = notificationsEnabled;
        this->refreshIntervalSeconds = refreshInterval;
    }

    void displayConfig() const {
        cout << "Dashboard Theme : " << theme << endl;
        cout << "Notifications Enabled : " << (notificationsEnabled ? "Yes" : "No") << endl;
        cout << "Refresh Interval : " << refreshIntervalSeconds << " seconds\n";
    }

    ~DashboardConfig() {
        cout << "Dashboard Config [" << theme << "] deleted\n";
        delete[] theme;
    }
};

class PaymentDashboard {
private:
    char* dashboardName;
    PlatformAccount** accounts;
    DashboardConfig* config;
    int accountCount;
    int capacity;

public:
    PaymentDashboard(const char* name, DashboardConfig* config) {
        dashboardName = new char[strlen(name) + 1];
        strcpy_s(dashboardName, strlen(name) + 1, name);

        this->config = config;
        capacity = 5;
        accountCount = 0;
        accounts = new PlatformAccount * [capacity];
    }

    void addAccount(PlatformAccount* account) {
        if (accountCount == capacity) {
            capacity *= 2;
            PlatformAccount** temp = new PlatformAccount * [capacity];

            for (int i = 0; i < accountCount; i++)
                temp[i] = accounts[i];

            delete[] accounts;
            accounts = temp;
        }

        accounts[accountCount] = account;
        accountCount++;
    }

    void displayDashboard() const {
        cout << "Payment Dashboard : " << dashboardName << endl;
        config->displayConfig();

        cout << "\n========= Accounts =========\n";
        for (int i = 0; i < accountCount; i++) {
            cout << "----------------------------\n";
            accounts[i]->displayAccountDetails();
        }
    }

    ~PaymentDashboard() {
        cout << "Payment Dashboard [" << dashboardName << "] deleted\n";
        delete[] dashboardName;
        delete config;      // owns config
        delete[] accounts;  // does NOT own accounts
    }
};

int main() {
    DashboardConfig* config = new DashboardConfig("Dark Mode", true, 30);

    PlatformAccount* acc1 = new PlatformAccount("Ali Khan", "ali@example.com", 1, "1234", "Standard", 1000.0, 500);
    PlatformAccount* acc2 = new PlatformAccount("Sara Ahmed", "sara@example.com", 2, "5678", "Premium", 2000.0, 1000);
    PremiumAccount* premAcc = new PremiumAccount("Ahmed Ali", "ahmed@example.com", 3, "9101", "Premium", 3000.0, 1500, "VIP123", 5.0);

    char pin[20];
    cout << "Enter PIN for Ali Khan: ";
    cin >> pin;

    bool authResult = acc1->authenticate(pin);

    while (!authResult) {
        cout << "Enter PIN again: ";
        cin >> pin;
        authResult = acc1->authenticate(pin);
    }

    PaymentDashboard* dashboard = new PaymentDashboard("My Payment Dashboard", config);

    dashboard->addAccount(acc1);
    dashboard->addAccount(acc2);
    dashboard->addAccount(premAcc);

    if (acc1->deposit(299.99))
        cout << "Deposit Successful\n";
    else
        cout << "Deposit Failed\n";

    if (acc1->withdraw(800))
        cout << "Withdrawal Successful\n";
    else
        cout << "Withdrawal Failed\n";

    double cashback = premAcc->calculateCashback(500);
    cout << "Cashback on $500 spent: $" << cashback << endl;

    dashboard->displayDashboard();

    delete dashboard;

    // accounts still exist
    acc1->displayAccountDetails();
    acc2->displayAccountDetails();
    premAcc->displayAccountDetails();

    delete acc1;
    delete acc2;
    delete premAcc;

    return 0;
}