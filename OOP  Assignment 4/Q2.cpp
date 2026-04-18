//#include<iostream>
//using namespace std;
//class Merchant {
//private:
//	char* merchantName;
//	char* merchantId;
//	double totalRevenue;
//	int transactionCount;
//public:
//	Merchant() :merchantName(nullptr), merchantId(nullptr), totalRevenue(0.0), transactionCount(0) {};
//	Merchant(const char* mrchnt, const char* mrchntId) {
//		merchantName = new char[strlen(mrchnt) + 1];
//		strcpy_s(merchantName, strlen(mrchnt) + 1, mrchnt);
//		
//		merchantId = new char[strlen(mrchntId) + 1];
//		strcpy_s(merchantId, strlen(mrchntId) + 1, mrchntId);
//		
//		totalRevenue = 0;
//		transactionCount = 0;
//	}
//	void display() const {
//		cout << "=======Merchant=======" << endl;
//		cout << "Merhcnat Id : " << merchantId << endl;
//		cout << "Merhcnat Name : " << merchantName << endl;
//		cout << "Total Revenue : $" << totalRevenue << endl;
//		cout << "Transaction Count : " << transactionCount << endl;
//
//	}
//	void recievePayment(double amount) {
//		totalRevenue += amount;
//		transactionCount += 1;
//	}
//	const char* getMerchantId() {
//		return merchantId;
//	}
//	~Merchant() {
//		cout << "Merchant [" << merchantName << "] deleted" << endl;
//		delete[] merchantName;
//		delete[] merchantId;
//		
//	}
//
//};
//class PaymentGateway {
//private:
//	char* gatewayName;
//	Merchant** merchants;
//	int merchantCount;
//	int capacity;
//public:
//	PaymentGateway(const char* gwayName) {
//		gatewayName = new char[strlen(gwayName) + 1];
//		strcpy_s(gatewayName, strlen(gwayName)+1, gwayName);
//		capacity = 5;
//		merchantCount = 0;
//		merchants = new Merchant * [capacity];
//
//	}
//	
//	void registerMerchant(Merchant* m) {
//		if (capacity == merchantCount) {
//			capacity *= 2;
//			Merchant** temp = new Merchant * [capacity];
//			for (int i = 0; i < merchantCount;i++) {
//				temp[i] = merchants[i];
//			}
//			delete[]merchants;
//			merchants = temp;
//		}
//		merchants[merchantCount++] = m;
//
//	}
//	void routePayment(const char* merchantId, double amount) {
//		for (int i = 0; i < merchantCount; i++) {
//			if (merchants[i]->getMerchantId() == merchantId) {
//				merchants[i]->recievePayment(amount);
//				return;
//			}
//		}
//		cout << "Merchant not found " << endl;
//	}
//	void displayAll() const {
//		cout << "Gateway : " << gatewayName << endl;
//		cout << "Merchant Count : " << merchantCount<<endl;
//		for (int i = 0; i < merchantCount; i++) {
//			merchants[i]->display();
//		}
//	}
//	~PaymentGateway() {
//		cout << "Payment Gateway [" << gatewayName << "] deleted" << endl;
//		delete[] gatewayName;
//		delete[]merchants;
//	}
//
//};
//int main() {
//	Merchant* M1 = new Merchant("Abdullah", "1001");
//	Merchant* M2 = new Merchant("Abdul Ahad", "1002");
//	Merchant* M3 = new Merchant("Abdullah Sahid", "1003");
//	PaymentGateway* Jazzcash = new PaymentGateway("Jazzcash");
//	Jazzcash->registerMerchant(M1);
//	Jazzcash->registerMerchant(M2);
//	Jazzcash->registerMerchant(M3);
//	Jazzcash->routePayment(M1->getMerchantId(), 100000);
//	Jazzcash->routePayment(M1->getMerchantId(), 59969);
//	Jazzcash->routePayment(M1->getMerchantId(), 9000);
//	Jazzcash->routePayment(M2->getMerchantId(), 100000);
//	Jazzcash->routePayment(M2->getMerchantId(), 59969);
//	Jazzcash->routePayment(M2->getMerchantId(), 9000);
//	Jazzcash->routePayment(M3->getMerchantId(), 100000);
//	Jazzcash->routePayment(M3->getMerchantId(), 59969);
//	Jazzcash->routePayment(M3->getMerchantId(), 9000);
//	Jazzcash->displayAll();
//	delete Jazzcash;
//	cout << "->>>>>Proof that Merchants still exist if the Payment Gateway is deleted<<<<<<-" << endl;
//	M1->display();
//	M2->display();
//	M3->display();
//	cout << "Manually Deleting the Merchants" << endl;
//	delete M1;
//	delete M2;
//	delete M3;
//	//Explanation for Aggregation
//	
//
//
//}