//#include<iostream>
//using namespace std;
//#include<cstring>
//class PaymentReceipt
//{
//private:
//	char* receiptId;
//	char* issuedTo;
//	unsigned long issuedAt;//timestamp
//	double confirmedAmount;
//	bool isPrinted;
//public:
//	PaymentReceipt(const char* rcpId, const char* isTo, unsigned long int timestmp, double cnfrmAmt, bool isPrnted) {
//		receiptId = new char[strlen(rcpId) + 1];
//		strcpy_s(receiptId, strlen(rcpId) + 1, rcpId);
//
//		issuedTo = new char[strlen(isTo) + 1];
//		strcpy_s(issuedTo, strlen(isTo) + 1, isTo);
//		isPrinted = isPrnted;
//		issuedAt = timestmp;
//		confirmedAmount = cnfrmAmt;
//	}
//	~PaymentReceipt() {
//		delete[] issuedTo;
//		delete[] receiptId;
//		cout << "CardPayment destroyed\n";
//	}
//	void markPrinted() {
//		isPrinted = true;
//
//	}
//	void printReceipt() const {
//		cout << "\n========== PAYMENT RECEIPT ==========\n";
// 		cout << "Receipt ID     : " << receiptId << endl;
//		cout << "Issued To      : " << issuedTo << endl;
//		cout << "Issued At      : " << issuedAt << endl;
//		cout << "Amount Paid    : $" << confirmedAmount << endl;
//		cout << "Printed Status : " << (isPrinted ? "Yes" : "No") << endl;
//		cout << "=====================================\n";
//	}
//};
//class Transaction {
//private:
//	char* transactionId;
//	double totalAmount;
//	char* status;
//	PaymentReceipt* receipt;
//public:
//	Transaction(const char* trnsId, const char* sts, double totAmt, PaymentReceipt* receipt, const char* rcpId, const char* isTo, unsigned long int timestmp, double cnfrmAmt, bool isPrnted) {
//		transactionId = new char[strlen(trnsId) + 1];
//		strcpy_s(transactionId, strlen(trnsId) + 1, trnsId);
//
//		status = new char[strlen(sts) + 1];
//		strcpy_s(status, strlen(sts) + 1, sts);
//
//		totalAmount = totAmt;
//
//		this->receipt = new PaymentReceipt(rcpId, isTo, timestmp, cnfrmAmt, isPrnted);
//	}
//	void complete() {
//		delete[]status;
//		status = new char[strlen("COMPLETED") + 1];
//		strcpy_s(status, strlen("COMPLETED") + 1, "COMPLETED");
//		receipt->markPrinted();
//	}
//
//	void fail() {
//		delete[]status;
//		status = new char[strlen("FAILED") + 1];
//		strcpy_s(status, strlen("FAILED") + 1, "FAILED");
//		delete receipt;
//		this->receipt = nullptr;
//	}
//	void display() const {
//		if (this->receipt != nullptr) {
//			receipt->printReceipt();
//		}
//		cout << "Transaction ID : " << transactionId << endl;
//		cout << "Status         : " << status << endl;
//		cout << "Total Amount   : $" << totalAmount << endl;
//		cout << "------------------------------------\n";
//	}
//	~Transaction() {
//		delete[] transactionId;
//		delete[] status;
//		if (receipt != nullptr) {
//			delete receipt;
//		}
//		cout << "Transaction destroyed\n";
//	}
//};
//class TransactionHistory {
//private:
//	Transaction** history;
//	int count;
//	int capacity;
//public:
//	TransactionHistory() {
//		cout << "Transaction History Constructor";
//		count = 0;
//		capacity = 5;
//		history = new Transaction * [capacity];
//
//	}
//	void addTransaction(Transaction* t) {
//		if (count == capacity) {
//			capacity *= 2;
//			Transaction** temp = new Transaction * [capacity];
//			for (int i = 0; i < count; i++) {
//				temp[i] = history[i];
//			}
//			delete[]history;
//			history = temp;
//		}
//		history[count] = t;
//		count++;
//	}
//	void removeTransaction(int index) {
//		if (index <= count) {
//			delete history[index];
//			for (int i = index; i < count; i++) {
//				history[i] = history[i + 1];
//			}
//		}
//
//		history[count - 1] = nullptr;
//		count--;
//
//	}
//	void displayAll() const {
//		for (int i = 0; i < count; i++) {
//			history[i]->display();
//		}
//	}
//	~TransactionHistory() {
//		for (int i = 0; i < count; i++) {
//			delete history[i];
//		}
//		delete[] history;
//		cout << "TransactionHistory destroyed\n";
//	}
//
//};
//int main() {
//
//	// 13. Create three Transaction objects
//	Transaction* t1 = new Transaction(
//		"T101", "PENDING", 1000,
//		nullptr,
//		"R101", "Ali", 1713000000, 1000, false
//	);
//
//	Transaction* t2 = new Transaction(
//		"T102", "PENDING", 2000,
//		nullptr,
//		"R102", "Sara", 1713000100, 2000, false
//	);
//
//	Transaction* t3 = new Transaction(
//		"T103", "PENDING", 1500,
//		nullptr,
//		"R103", "Ahmed", 1713000200, 1500, false
//	);
//
//	// Complete two, fail one
//	t1->complete();
//	t2->complete();
//	t3->fail();
//	 
//	// 14. Add to TransactionHistory
//	TransactionHistory history;
//	history.addTransaction(t1);
//	history.addTransaction(t2);
//	history.addTransaction(t3);
//	// 15. Display history
//	history.displayAll();
//
//	
//	// 16. Remove failed transaction (index 2)
//	cout << "\n--- REMOVING FAILED TRANSACTION ---\n";
//	history.removeTransaction(2);
//	t3->display(); // This will give error because we have deleted the transaction in removeTransaction function and set it to nullptr
//
//	// Display again
//	cout << "\n--- AFTER REMOVAL ---\n";
//	cout << "\n--- ALL TRANSACTIONS ---\n";
//	history.displayAll();
//
//	// 17. End of scope → destructor chain runs automatically
//	cout << "\n--- END OF PROGRAM ---\n";
//	// if we call read recipt of failed transaction it will give error because we have deleted the receipt in fail function and set it to nullptr
//	// In this code, the Transaction class creates and manages the lifecycle of the PaymentReceipt object.
//	// This means that the Transaction class is responsible for creating the PaymentReceipt when a Transaction is created and deleting it when the Transaction is destroyed.
//	// This is an example of composition, where one class (Transaction) owns and manages the lifecycle of another class (PaymentReceipt).
//	// If the PaymentReceipt were created outside of the Transaction and passed in by pointer, then the Transaction would not be responsible for managing its lifecycle, and it would be an example of aggregation instead.
//	// Demonstrating a dangling pointer:
//	// If we call t3->receipt->printReceipt() after calling t3->fail(), it would result in a dangling pointer because the fail() method deletes the receipt and sets the pointer to nullptr.
//	// Uncommenting the following line would cause a runtime error due to dereferencing a dangling pointer:
//	// t3->receipt->printReceipt();
//	
//
//	return 0;
//}
