//#include <iostream>
//#include <cstring>
//using namespace std;
//
//class Payment {
//private:
//    char* ownerName;
//    double amount;
//    int paymentId;
//    char* currency;
//
//public:
//     //Constructor
//    Payment(const char* name, double amt, int id, const char* curr) {
//        ownerName = new char[strlen(name) + 1];
//        strcpy_s(ownerName, strlen(name) + 1, name);
//
//        currency = new char[strlen(curr) + 1];
//        strcpy_s(currency, strlen(curr) + 1, curr);
//
//        amount = amt;
//        paymentId = id;
//    }
//
//    // Destructor
//    ~Payment() {
//        cout << "Payment [" << paymentId << "] destroyed\n";
//        delete[] ownerName;
//        delete[] currency;
//    }
//
//    // Display
//    void display() const {
//		cout << "Payment Details:\n";
//        cout << "Owner: " << ownerName << endl;
//        cout << "Amount: " << amount << endl;
//        cout << "Payment ID: " << paymentId << endl;
//        cout << "Currency: " << currency << endl;
//    }
//
//    // Getters
//    double getAmount() const { 
//        return amount; 
//    }
//
//    const char* getOwnerName() const { 
//        return ownerName; 
//    }
//    const char* getCurrency() const { 
//        return currency; 
//    }
//    int getPaymentId() const { 
//        return paymentId; 
//    }
//
//    // Setters
//    void setOwnerName(const char* name) {
//        delete[] ownerName;
//        ownerName = new char[strlen(name) + 1];
//        strcpy_s(ownerName, strlen(name) + 1, name);
//    }
//
//    void setCurrency(const char* curr) {
//        delete[] currency;
//        currency = new char[strlen(curr) + 1];
//        strcpy_s(currency, strlen(curr) + 1, curr);
//    }
//
//    void setAmount(double amt) { 
//        amount = amt; 
//    }
//    void setPaymentId(int id) { 
//        paymentId = id; 
//    }
//};
//
//
//class OnlinePayment : public Payment {
//private:
//    char* platform;
//    char* transactionRef;
//    bool isVerified;
//
//public:
//    // Constructor
//    OnlinePayment(const char* name, double amt, unsigned int id, const char* curr,
//        const char* plat, const char* ref)
//        : Payment(name, amt, id, curr), isVerified(false)
//    {
//        platform = new char[strlen(plat) + 1];
//        strcpy_s(platform, strlen(plat) + 1, plat);
//
//        transactionRef = new char[strlen(ref) + 1];
//        strcpy_s(transactionRef, strlen(ref) + 1, ref);
//    }
//
//    // Verify function
//    void verify() {
//        isVerified = true;
//        cout << "Payment verified successfully!\n";
//    }
//
//    // Display
//    void display() const{
//        Payment::display();
//		cout << "Online Payment Details:\n";
//        cout << "Platform: " << platform << endl;
//        cout << "Transaction Ref: " << transactionRef << endl;
//        cout << "Verified: " << (isVerified ? "Yes" : "No") << endl;
//    }
//
//    // Destructor
//    ~OnlinePayment() {
//        delete[] platform;
//        delete[] transactionRef;
//        cout << "OnlinePayment destroyed\n";
//    }
//};
//
//class CardPayment : public OnlinePayment {
//private:
//    char* maskedCardNumber;
//    char* cardType;
//    int expiryYear, expiryMonth;
//
//public:
//    // Constructor
//    CardPayment(const char* name, double amt, unsigned int id, const char* curr,
//        const char* plat, const char* ref,
//        const char* cardNum, const char* type,
//        int year, int month)
//        : OnlinePayment(name, amt, id, curr, plat, ref)
//    {
//        maskedCardNumber = new char[strlen(cardNum) + 1];
//        strcpy_s(maskedCardNumber, strlen(cardNum) + 1, cardNum);
//
//        cardType = new char[strlen(type) + 1];
//        strcpy_s(cardType, strlen(type) + 1, type);
//
//        expiryYear = year;
//        expiryMonth = month;
//    }
//
//    // Expiry check
//    bool isExpired(int currentYear, int currentMonth) const {
//        if (expiryYear < currentYear) 
//            return true;
//        if (expiryYear == currentYear && expiryMonth < currentMonth) return true;
//        return false;
//    }
//
//    // Display
//    void display() const {
//        OnlinePayment::display();
//		  cout << "Card Payment Details:\n";
//        cout << "Card Number: " << maskedCardNumber << endl;
//        cout << "Card Type: " << cardType << endl;
//        cout << "Expiry: " << expiryMonth << "/" << expiryYear << endl;
//    }
//
//    // Destructor
//    ~CardPayment() {
//        delete[] maskedCardNumber;
//        delete[] cardType;
//        cout << "CardPayment destroyed\n";
//    }
//};
//
//int main() {
//    
//    CardPayment* cardPtr = new CardPayment(
//        "Ali Khan", 5000.75, 101, "PKR",
//        "JazzCash", "TXN12345",
//        "****1234", "VISA",
//        2025, 12
//    );
//
//    cout << "\n--- DISPLAY ---\n";
//    // 2. Display
//    cardPtr->display();
//    //calling display using Payment ptr
//	Payment* paymentPtr = cardPtr;
//	paymentPtr->display();//only Payment details are shown
//	//using virtual will display all details of CardPayment class when called through Payment pointer
//    //we will use virtual keyword in display function of base class or Payment class to show CardPayment Details
//    cout << "\n--- VERIFY ---\n";
//    // 3. Verify
//    cardPtr->verify();
//
//    cout << "\n--- EXPIRY CHECK ---\n";
//    bool expired = cardPtr->isExpired(2026, 3);
//
//    // 4. Print result
//    if (expired)
//        cout << "Card is expired\n";
//    else                                                           
//        cout << "Card is valid\n";
//
//    cout << "\n--- DESTRUCTOR CHAIN ---\n";
//    // 5. Delete
//    
//    delete cardPtr;
//	
//
//    return 0;
//}