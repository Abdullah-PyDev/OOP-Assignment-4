#include<iostream>
#include<cstring>
using namespace std;
//user profile class
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
	const char* getUsername() const { 
        return username; 
    }
	const char* getEmail() const { 
        return email; 
    }
  
    int getUserId() const { 
        return userId; 
	}
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
    PlatformAccount* accounts[5] = { nullptr };

    DashboardConfig* config = new DashboardConfig("Dark Mode", true, 30);
    PaymentDashboard* dashboard = new PaymentDashboard("My Payment Dashboard", config);

    while (true) {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Display Dashboard\n";
        cout << "2. Create Dashboard\n";
        cout << "3. Authenticate Account\n";
        cout << "4. Add Account\n";
        cout << "5. Delete Account\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            dashboard->displayDashboard();
        }

        else if (choice == 2) {
            char name[100], theme[50];

            cout << "Set Dashboard Name: ";
            cin >> name;

            cout << "Set Dashboard Theme: ";
            cin >> theme;

            delete config;
            config = new DashboardConfig(theme, true, 30);

            delete dashboard;
            dashboard = new PaymentDashboard(name, config);

            cout << "Dashboard created successfully!\n";
        }

        else if (choice == 3) {
            int userId;
            cout << "Enter User ID: ";
            cin >> userId;

            int index = -1;

            for (int i = 0; i < 5; i++) {
                if (accounts[i] != nullptr && accounts[i]->getUserId() == userId) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                cout << "Account not found!\n";
                continue;
            }

            char pin[20];
            cout << "Enter PIN: ";
            cin >> pin;

            if (accounts[index]->authenticate(pin)) {
                cout << "Login successful!\n";

                while (true) {
                    cout << "\n--- ACCOUNT MENU ---\n";
                    cout << "1. Display\n2. Deposit\n3. Withdraw\n4. Logout\n";
                    int ch;
                    cin >> ch;

                    if (ch == 1)
                        accounts[index]->displayAccountDetails();

                    else if (ch == 2) {
                        double amt;
                        cin >> amt;
                        accounts[index]->deposit(amt);
                    }

                    else if (ch == 3) {
                        double amt;
                        cin >> amt;
                        accounts[index]->withdraw(amt);
                    }

                    else break;
                }
            }
        }

        else if (choice == 4) {
            int slot = -1;

            for (int i = 0; i < 5; i++) {
                if (accounts[i] == nullptr) {
                    slot = i;
                    break;
                }
            }

            if (slot == -1) {
                cout << "Account storage full!\n";
                continue;
            }

            char uname[50], email[50], pin[20], type[20];
            int id, limit;
            double bal;

            cout << "Enter Username: "; cin >> uname;
            cout << "Enter Email: "; cin >> email;
            cout << "Enter ID: "; cin >> id;
            cout << "Enter PIN: "; cin >> pin;
            cout << "Enter Type: "; cin >> type;
            cout << "Enter Balance: "; cin >> bal;
            cout << "Enter Limit: "; cin >> limit;

            PlatformAccount* acc =
                new PlatformAccount(uname, email, id, pin, type, bal, limit);

            accounts[slot] = acc;
            dashboard->addAccount(acc);

            cout << "Account added!\n";
        }

        else if (choice == 5) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;

            for (int i = 0; i < 5; i++) {
                if (accounts[i] != nullptr && accounts[i]->getUserId() == id) {
                    delete accounts[i];
                    accounts[i] = nullptr;
                    cout << "Deleted!\n";
                }
            }
        }

        else if (choice == 6) {
            break;
        }
    }

    // cleanup
    delete dashboard;

    for (int i = 0; i < 5; i++) {
        if (accounts[i] != nullptr)
            delete accounts[i];
    }

    return 0;
}