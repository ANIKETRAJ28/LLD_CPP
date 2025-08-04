#include <iostream>
using namespace std;

class Account
{
protected:
  double balance;

public:
  Account(double balance)
  {
    if (balance < 0)
      throw invalid_argument("Balance can't be negative");
    this->balance = balance;
  }
  virtual void withdraw(double amount)
  {
    if (balance - amount < 0)
      throw runtime_error("Insufficient funds");
    balance -= amount;
    cout << "Amount withdrawn. Remaining balance is " << balance << endl;
  }
};

// Breaks invariant rule, should not be allowed
class CheatAccount : public Account
{
public:
  CheatAccount(double balance) : Account(balance) {}
  void withdraw(double amount) override
  {
    balance -= amount; // LSP breaks! negative balance is not allowed
    cout << "Amount withdrawn. Remaining balance is " << balance << endl;
  }
};

int main()
{
  Account *account = new CheatAccount(100);
  account->withdraw(200);

  return 0;
}