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
class FixedAccount : public Account
{
public:
  FixedAccount(double balance) : Account(balance) {}
  void withdraw(double amount) override
  {
    // LSP breaks! withdrawal should be allowed in all the accounts
    throw runtime_error("Withdrawal not allowed in Fixed Account");
  }
};

int main()
{
  Account *account = new FixedAccount(100);
  account->withdraw(200);

  return 0;
}