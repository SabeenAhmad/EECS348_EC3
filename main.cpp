#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Account{
    protected:
    string accountNumber;
    string accountHolder;
    float balance;
    public:
        Account(const string acctNum, const string acctHolder, float acctBalance)
        : accountNumber(acctNum), accountHolder(acctHolder), balance(acctBalance) {};


    virtual void displayDetails() const{
        cout<< "Account Details for " << getAccountType() << "(ID: "<< accountNumber << ")"<< endl;
        cout << "Holder: "<< accountHolder<<endl;
        cout << fixed << setprecision(2) <<  "Balance: $" << balance << endl;
    }

    virtual void deposit(float amount) {
        if(amount > 0){
            balance+= amount;
        }
    }
    virtual void withdraw(float amount){
        if(amount <= balance){
            balance-= amount;
        }
    }

    
    virtual string getAccountType() const{
        return "Account";
    }
    float getBalance() {
        return balance;
    }
};
    class SavingsAccount : public Account{
    public:
    float interestRate;
    SavingsAccount(const string acctNum, const string acctHolder, float acctBalance, float interestRate)
    : Account(acctNum, acctHolder,acctBalance),interestRate(interestRate){};

    void displayDetails() const{
        cout<< "Account Details for " << getAccountType() << "(ID: "<< accountNumber << ")"<< endl;
        cout << "   Holder: "<< accountHolder<<endl;
        cout << fixed << setprecision(2) <<  "   Balance: $" << balance << endl;
        cout << "   Interest rate: "<< float(interestRate *100) <<"%"<<endl;
    }

    string getAccountType() const{
        return "Savings Account";
    }
    void withdraw(float amount){
        if(amount <= balance && balance - amount >=50){
            balance-= amount;
        }
        else{
            cout << "Your balance will be less than $50 if you withdraw "<< amount << "therefore, you can not withdraw"<<endl;
        }
    };

    };
     class CurrentAccount : public Account{
        public:
        float overDraftLimit;
        CurrentAccount(const string acctNum, const string acctHolder, float acctBalance, float overDraftLimit)
            : Account(acctNum, acctHolder,acctBalance),overDraftLimit(overDraftLimit){};

        void displayDetails() const{
        cout<< "Account Details for " << getAccountType() << "(ID: "<< accountNumber << ")"<< endl;
        cout << "   Holder: "<< accountHolder<<endl;
        cout << fixed << setprecision(2) <<  "   Balance: $" << balance << endl;
        cout << "   Overdraft Limit: $"<< overDraftLimit <<endl;
        }
        void withdraw(float amount){
            if (amount > (balance + overDraftLimit)){
                cout << "You cannot withdraw that much " << endl;
            }
            else{
                 balance -= amount;
            }
        };
        string getAccountType() const{
        return "Current Account";
    }
     };
    CurrentAccount operator+(CurrentAccount current, SavingsAccount& savings) {
    if (savings.getBalance() >= 300 ) {
        current.deposit(300);
        savings.withdraw(300);
    }
    return current;
}
int main() {

    SavingsAccount Savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount Current("C456", "Jane Doe", 2000, 500);

    Savings.displayDetails();
    Current.displayDetails();

    cout << "Account Details after deposit and withdrawal: " << endl;

    Savings.deposit(500);
    Current.withdraw(1000);
    
    Savings.displayDetails();
    Current.displayDetails();


    cout << "Account Details after transfer: " << endl;
    Current = Current + Savings;

    Savings.displayDetails();
    Current.displayDetails();

   return 0;
}