#include<iostream>
#include<memory>
#include <utility>

using namespace std;

class PaymentStrategy {
    public:
        virtual void processPayment(double amount) = 0;
        virtual ~PaymentStrategy() {};
};
class CreditCardPayment: public PaymentStrategy {
    public:
        void processPayment(double amount) {
            cout << "Payment Processed by CC of " << amount << endl;
        }
};
class PayPalPayment: public PaymentStrategy {
    public:
        void processPayment(double amount) {
            cout << "Payment Processed by Paypal of " << amount << endl;
        }
};

class PaymentProcessor {
    private:
        unique_ptr<PaymentStrategy> strategy;
    public:
        void setPaymentStrategy (unique_ptr<PaymentStrategy> pStrategy) {
            strategy = std::move(pStrategy);
        }
        void processPayment (double amount) {
            if (strategy) {
                strategy->processPayment(amount);
            } else {
                cout << "Payment Strategy not SET";
            }
        }
};

int main() {
    PaymentProcessor processor;  // decides strategy

    // error showing at make_unique, compile it with -std=c++17
    processor.setPaymentStrategy(make_unique<CreditCardPayment>());
    processor.processPayment(98.0);

    processor.setPaymentStrategy(make_unique<PayPalPayment>());
    processor.processPayment(50.0);

    return 0;
}