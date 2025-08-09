#include <iostream>
using namespace std;

// Burger class
class Burger
{
public:
  virtual void prepare() = 0;
};

// basic burger class
class BasicBurger : public Burger
{
public:
  void prepare() override
  {
    cout << "Preparing basic burger..." << endl;
  }
};

// standard burger class
class StandardBurger : public Burger
{
public:
  void prepare() override
  {
    cout << "Preparing standard burger..." << endl;
  }
};

// premium burger class
class PremiumBurger : public Burger
{
public:
  void prepare() override
  {
    cout << "Preparing premium burger..." << endl;
  }
};

// factory class
class Factory
{
public:
  Burger *createBurger(string type)
  {
    if (type == "basic")
    {
      return new BasicBurger();
    }
    else if (type == "standard")
    {
      return new StandardBurger();
    }
    else if (type == "premium")
    {
      return new PremiumBurger();
    }
    else
    {
      cout << "Invalid burger type..." << endl;
      return nullptr;
    }
  }
};

int main()
{
  Factory *burgerFactory = new Factory();
  Burger *basic = burgerFactory->createBurger("basic");
  Burger *standard = burgerFactory->createBurger("standard");
  Burger *premium = burgerFactory->createBurger("premium");
  basic->prepare();
  standard->prepare();
  premium->prepare();
  return 0;
}