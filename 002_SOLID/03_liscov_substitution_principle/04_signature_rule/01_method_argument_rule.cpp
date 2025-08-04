#include <iostream>
using namespace std;

// Method argument rule
// Subtype method arguments can be identical or broader than the supertype
// C++ imposes this by keeping signature identical

class Parent
{
public:
  virtual void print(string msg)
  {
    cout << "Parent : " << msg << endl;
  }
};

// Client that pass string as msg as client expects
class Child : public Parent
{
public:
  void print(string msg) override
  {
    cout << "Child : " << msg << endl;
  }
};

class Client
{
private:
  Parent *p;

public:
  Client(Parent *p)
  {
    this->p = p;
  }
  void printMsg()
  {
    p->print("Hello");
  }
};

int main()
{
  Parent *parent = new Parent();
  Parent *child = new Child();

  Client *client1 = new Client(parent);
  Client *client2 = new Client(child);

  client1->printMsg();
  client2->printMsg();

  return 0;
}