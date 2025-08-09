#include <iostream>
using namespace std;

// burger class
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

// basic wheat burger class
class BasicWheatBurger : public Burger
{
public:
  void prepare() override
  {
    cout << "Preparing basic wheat burger..." << endl;
  }
};

// standard wheat burger class
class StandardWheatBurger : public Burger
{
public:
  void prepare() override
  {
    cout << "Preparing standard wheat burger..." << endl;
  }
};

// premium wheat burger class
class PremiumWheatBurger : public Burger
{
public:
  void prepare() override
  {
    cout << "Preparing premium wheat burger..." << endl;
  }
};

// factory class
class Factory
{
public:
  virtual Burger *createBurger(string type) = 0;
};

// singh burger frencise (creates only wheat burgers)
class SinghBurger : public Factory
{
public:
  Burger *createBurger(string type) override
  {
    if (type == "basic")
    {
      return new BasicWheatBurger();
    }
    else if (type == "standard")
    {
      return new StandardWheatBurger();
    }
    else if (type == "premium")
    {
      return new PremiumWheatBurger();
    }
    else
    {
      cout << "Invalid burger type..." << endl;
      return nullptr;
    }
  }
};

// king burger frencise (creates only normal burgers)
class KingBurger : public Factory
{
public:
  Burger *createBurger(string type) override
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
  Factory *singhFactory = new SinghBurger();
  Burger *singhBasicBurger = singhFactory->createBurger("basic");
  Burger *singhStandardBurger = singhFactory->createBurger("standard");
  Burger *singhPremiumBurger = singhFactory->createBurger("premium");
  Factory *kingBurger = new KingBurger();
  Burger *kingBasicBurger = kingBurger->createBurger("basic");
  Burger *kingStandardBurger = kingBurger->createBurger("standard");
  Burger *kingPremiumBurger = kingBurger->createBurger("premium");

  singhBasicBurger->prepare();
  singhStandardBurger->prepare();
  singhPremiumBurger->prepare();
  kingBasicBurger->prepare();
  kingStandardBurger->prepare();
  kingPremiumBurger->prepare();
  return 0;
}