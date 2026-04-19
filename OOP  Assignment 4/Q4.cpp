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

    UserProfile(const char* uname, const char* mail, int uId) {
        username = new char[strlen(uname) + 1];
        strcpy_s(username, strlen(uname) + 1, uname);

        email = new char[strlen(mail) + 1];
        strcpy_s(email, strlen(mail) + 1, mail);

        userId = uId;
    }

    const char* getUsername() const { return username; }
    const char* getEmail() const { return email; }
    int getUserId() const { return userId; }

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

    bool authenticate(const char* pin) {
        if (isLocked) {
            cout << "Account is locked!\n";
            return false;
        }

        if (strcmp(pin, hashedPin) == 0) {
            failedAttempts = 0;
            return true;
        }

        failedAttempts++;
        cout << "Incorrect PIN\n";

        if (failedAttempts >= 3) {
            isLocked = true;
            cout << "Account locked after 3 failed attempts!\n";
        }

        return false;
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
protected:
    char* accountType;
    double balance;
    int transactionLimit;

public:
    PlatformAccount(const char* uname, const char* email, int uId,
        const char* hPin, const char* accType,
        double bal, int transLimit)
        : UserProfile(uname, email, uId),
        SecurityModule(hPin) {

        accountType = new char[strlen(accType) + 1];
        strcpy_s(accountType, strlen(accType) + 1, accType);

        balance = bal;
        transactionLimit = transLimit;
    }

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
        const char* vip, double cashback)
        : PlatformAccount(uname, email, uId, hPin, accType, bal, transLimit) {

        vipCode = new char[strlen(vip) + 1];
        strcpy_s(vipCode, strlen(vip) + 1, vip);

        cashbackRate = cashback;
    }

    void displayPremiumDetails() const {
        displayAccountDetails();
        cout << "VIP Code : " << (vipCode ? vipCode : "NULL") << endl;
        cout << "Cashback Rate : " << cashbackRate << "%\n";
    }

    double calculateCashback(double spent) const {
        return spent * (cashbackRate / 100);
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
    DashboardConfig(const char* t, bool n, int r) {
        theme = new char[strlen(t) + 1];
        strcpy_s(theme, strlen(t) + 1, t);

        notificationsEnabled = n;
        refreshIntervalSeconds = r;
    }

    void displayConfig() const {
        cout << "Dashboard Theme : " << theme << endl;
        cout << "Notifications : " << (notificationsEnabled ? "Yes" : "No") << endl;
        cout << "Refresh : " << refreshIntervalSeconds << " sec\n";
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
    int accountCount;
    int capacity;
    DashboardConfig* config; // NOT owned anymore

public:
    PaymentDashboard(const char* name, DashboardConfig* cfg) {
        dashboardName = new char[strlen(name) + 1];
        strcpy_s(dashboardName, strlen(name) + 1, name);

        config = cfg;

        capacity = 5;
        accountCount = 0;
        accounts = new PlatformAccount * [capacity];
    }

    void addAccount(PlatformAccount* acc) {
        if (accountCount == capacity) {
            capacity *= 2;
            PlatformAccount** temp = new PlatformAccount * [capacity];

            for (int i = 0; i < accountCount; i++)
                temp[i] = accounts[i];

            delete[] accounts;
            accounts = temp;
        }

        accounts[accountCount++] = acc;
    }

    void displayDashboard() const {
        cout << "Payment Dashboard: " << dashboardName << endl;
        config->displayConfig();

        cout << "\n--- Accounts ---\n";
        for (int i = 0; i < accountCount; i++) {
            cout << "-----------------\n";
            accounts[i]->displayAccountDetails();
        }
    }

    // IMPORTANT: does NOT delete accounts or config
    ~PaymentDashboard() {
        cout << "Dashboard [" << dashboardName << "] deleted\n";
        delete[] dashboardName;
        delete[] accounts;
    }
};


int main() {
    PlatformAccount* accounts[5] = { nullptr };

    DashboardConfig* config = new DashboardConfig("Dark Mode", true, 30);
    PaymentDashboard* dashboard = new PaymentDashboard("My Dashboard", config);

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Display Dashboard\n2. Add Account\n3. Authenticate\n4. Delete Account\n5. Exit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            dashboard->displayDashboard();
        }

        else if (choice == 2) {
            int slot = -1;
            for (int i = 0; i < 5; i++)
                if (!accounts[i]) { slot = i; break; }

            if (slot == -1) {
                cout << "Full!\n";
                continue;
            }

            char type;
            cout << "Premium? (y/n): ";
            cin >> type;

            char u[50], e[50], p[20], acc[20], vip[20];
            int id, lim;
            double bal, cash;

            cout << "Username: "; 
            cin >> u;
            cout << "Email: "; 
            cin >> e;
            cout << "ID: "; 
            cin >> id;
            cout << "PIN: "; 
            cin >> p;
            cout << "Type: "; 
            cin >> acc;
            cout << "Balance: "; 
            cin >> bal;
            cout << "Limit: "; 
            cin >> lim;

            if (type == 'y') {
                cout << "VIP: "; 
                cin >> vip;
                cout << "Cashback: "; 
                cin >> cash;

                accounts[slot] = new PremiumAccount(u, e, id, p, acc, bal, lim, vip, cash);
            }
            else {
                accounts[slot] = new PlatformAccount(u, e, id, p, acc, bal, lim);
            }

            dashboard->addAccount(accounts[slot]);
            cout << "Added!\n";
        }

        else if (choice == 3) {
            int id;
            cout << "User ID: ";
            cin >> id;

            int idx = -1;
            for (int i = 0; i < 5; i++)
                if (accounts[i] && accounts[i]->getUserId() == id)
                    idx = i;

            if (idx == -1) {
                cout << "Not found\n";
                continue;
            }

            char pin[20];
            cout << "PIN: ";
            cin >> pin;

            if (accounts[idx]->authenticate(pin)) {
                cout << "Login success!\n";
            }
        }

        else if (choice == 4) {
            int id;
            cout << "Delete ID: ";
            cin >> id;

            for (int i = 0; i < 5; i++) {
                if (accounts[i] && accounts[i]->getUserId() == id) {
                    delete accounts[i];
                    accounts[i] = nullptr;
                    cout << "Deleted\n";
                }
            }
        }

        else if (choice == 5) break;
    }

    delete dashboard;

    for (int i = 0; i < 5; i++)
        delete accounts[i];

    delete config;

    return 0;
}