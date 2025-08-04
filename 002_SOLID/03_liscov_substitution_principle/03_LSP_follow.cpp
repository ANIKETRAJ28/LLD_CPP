#include <iostream>
#include <vector>
using namespace std;

class NonWithDrawalAccount
{
public:
  virtual void deposit(double amount) = 0;
};

class WithDrawalAccount : public NonWithDrawalAccount
{
public:
  virtual void withdrawal(double amount) = 0;
};

class SavingsAccount : public WithDrawalAccount
{
private:
  double balance;

public:
  SavingsAccount()
  {
    balance = 0;
  }

  void deposit(double amount)
  {
    balance += amount;
    cout << "Deposited: " << amount << " in Savings Account. New Balance is $" << balance << endl;
  }

  void withdrawal(double amount)
  {
    if (amount > balance)
    {
      cout << "Insufficient balance in Savings Account" << endl;
    }
    else
    {
      balance -= amount;
      cout << "Withdrawn: $" << amount << " from Savings Account. New Balance: " << balance << endl;
    }
  }
};

class CurrentAccount : public WithDrawalAccount
{
private:
  double balance;

public:
  CurrentAccount()
  {
    balance = 0;
  }

  void deposit(double amount)
  {
    balance += amount;
    cout << "Deposited: " << amount << " in Current Account. New Balamce is $" << balance << endl;
  }

  void withdrawal(double amount)
  {
    if (amount > balance)
    {
      cout << "Insufficient balance in Current Account" << endl;
    }
    else
    {
      balance -= amount;
      cout << "Withdrawn: $" << amount << " from Current Account. New Balance: " << balance << endl;
    }
  }
};

class FixedTermAccount : public NonWithDrawalAccount
{
private:
  double balance;

public:
  FixedTermAccount()
  {
    balance = 0;
  }

  void deposit(double amount)
  {
    balance += amount;
    cout << "Deposited: " << amount << " in Fixed Term Account. New Balamce is $" << balance << endl;
  }
};

class BankClient
{
private:
  vector<WithDrawalAccount *> withdrawalAccounts;
  vector<NonWithDrawalAccount *> nonWithDrawalAccounts;

public:
  BankClient(vector<WithDrawalAccount *> withdrawalAccounts, vector<NonWithDrawalAccount *> nonWithDrawalAccounts)
  {
    this->withdrawalAccounts = withdrawalAccounts;
    this->nonWithDrawalAccounts = nonWithDrawalAccounts;
  }

  void processTransaction()
  {
    for (WithDrawalAccount *acc : withdrawalAccounts)
    {
      acc->deposit(1000);
      acc->withdrawal(500);
    }
    for (NonWithDrawalAccount *acc : nonWithDrawalAccounts)
    {
      acc->deposit(1000);
    }
  }
};

int main()
{
  vector<WithDrawalAccount *> withDrawalAcounts;
  vector<NonWithDrawalAccount *> nonWithDrawalAccounts;
  withDrawalAcounts.push_back(new SavingsAccount());
  withDrawalAcounts.push_back(new CurrentAccount());
  nonWithDrawalAccounts.push_back(new FixedTermAccount());

  BankClient *client = new BankClient(withDrawalAcounts, nonWithDrawalAccounts);
  client->processTransaction();
}
