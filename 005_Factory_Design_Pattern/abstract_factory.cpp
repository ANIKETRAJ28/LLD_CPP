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

class Bread
{
public:
  virtual void prepare() = 0;
};

// basic bread class
class BasicBread : public Bread
{
public:
  void prepare() override
  {
    cout << "Preparing basic bread..." << endl;
  }
};

// standard bread class
class StandardBread : public Bread
{
public:
  void prepare() override
  {
    cout << "Preparing standard bread..." << endl;
  }
};

// premium bread class
class PremiumBread : public Bread
{
public:
  void prepare() override
  {
    cout << "Preparing premium bread..." << endl;
  }
};

// factory class
class Factory
{
public:
  virtual Burger *createBurger(string type) = 0;
  virtual Bread *createBread(string type) = 0;
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
  Bread *createBread(string type) override
  {
    if (type == "basic")
    {
      return new BasicBread();
    }
    else if (type == "standard")
    {
      return new StandardBread();
    }
    else if (type == "premium")
    {
      return new PremiumBread();
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
  Bread *createBread(string type) override
  {
    if (type == "basic")
    {
      return new BasicBread();
    }
    else if (type == "standard")
    {
      return new StandardBread();
    }
    else if (type == "premium")
    {
      return new PremiumBread();
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
  Bread *singhBasicBread = singhFactory->createBread("basic");
  Bread *singhStandardBread = singhFactory->createBread("standard");
  Bread *singhPremiumBread = singhFactory->createBread("premium");
  Factory *kingFactory = new KingBurger();
  Burger *kingBasicBurger = kingFactory->createBurger("basic");
  Burger *kingStandardBurger = kingFactory->createBurger("standard");
  Burger *kingPremiumBurger = kingFactory->createBurger("premium");
  Bread *kingBasicBread = kingFactory->createBread("basic");
  Bread *kingStandardBread = kingFactory->createBread("standard");
  Bread *kingPremiumBread = kingFactory->createBread("premium");

  singhBasicBurger->prepare();
  singhStandardBurger->prepare();
  singhPremiumBurger->prepare();
  kingBasicBurger->prepare();
  kingStandardBurger->prepare();
  kingPremiumBurger->prepare();
  cout << "-------------\n";
  singhBasicBread->prepare();
  singhStandardBread->prepare();
  singhPremiumBread->prepare();
  kingBasicBread->prepare();
  kingStandardBread->prepare();
  kingPremiumBread->prepare();
  return 0;
}