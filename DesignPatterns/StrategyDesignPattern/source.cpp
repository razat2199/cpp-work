#include<iostream>

using namespace std;

class PaymentStrategy {
    public:
        virtual void processPayment(double amount) = 0;
        virtual ~PaymentStrategy() {};
};
class CreditCardPayment: public PaymentStrategy {
    public:
        void processPayment(double amount) override {
            cout << "Payment Processed by CC of " << amount << endl;
        }
};
class PayPalPayment: public PaymentStrategy {
    public:
        void processPayment(double amount) override {
            cout << "Payment Processed by Paypal of " << amount << endl;
        }
};

class PaymentProcessor {
    private:
        PaymentStrategy* strategy;
    public:
        PaymentProcessor (): strategy(nullptr) {}
        void setPaymentStrategy (PaymentStrategy* pStrategy) {
            if (strategy) delete strategy;
            strategy = pStrategy;
        }
        void processPayment (double amount) {
            if (strategy) {
                strategy->processPayment(amount);
            } else {
                cout << "Payment Strategy not SET";
            }
        }
        ~PaymentProcessor() {
            if (strategy) delete strategy;
        }
};

int main() {
    PaymentProcessor processor;  // decides strategy

    PaymentStrategy* strategy = new CreditCardPayment();
    processor.setPaymentStrategy(strategy);
    processor.processPayment(100.0);

    // delete strategy; // clean up previous strategy
    // this delete can be removed and delete strategy can be done
    // from processor, before setPaymentStrategy

    strategy  = new PayPalPayment();
    processor.setPaymentStrategy(strategy);
    processor.processPayment(50.0);

    //delete strategy;  causing segmentation fault
    return 0;
}