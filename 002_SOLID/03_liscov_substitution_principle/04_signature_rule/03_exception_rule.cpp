#include <iostream>
using namespace std;

// Exception Rule:
// A subclass should exact or narrower exceptions
// but not additional or broader exceptions than the parent
// C++ does not enforces this. So, no compiletime errors

/**
 * |--std:logic_error           <-- For logic errors detected before runtime
 * |  |--std::invalid_argument  <-- Invalid function arguments
 * |  |--std::domain_error      <-- Function argument domain error
 * |  |--std::length_error      <-- Exceeding valid length limits
 * |  |--std::out_of_range      <-- Array or container index out of bound
 * |
 * |--std::runtime_error        <-- For errors that occur at runtime
 * |  |--std::range_error       <-- Numeric results out of range
 * |  |--std::overflow_error    <-- Arithmetic overflow
 * |  |--std::underflow_error
 */

class Parent
{
public:
  // noexcept(false) is c++ keyword which give user the idea that the function will throw an error
  virtual void getValue() noexcept(false)
  { // Parent throws logic_error exception
    throw logic_error("Parent error");
  }
};

class Child : public Parent
{
public:
  void getValue() noexcept(false) override
  {
    throw out_of_range("Child error");
    // throw runtime_error("Child error"); // throws error
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

  void takeValue()
  {
    try
    {
      p->getValue();
    }
    catch (const logic_error &e)
    {
      cout << "Logic error exception occured : " << e.what() << endl;
    }
  }
};

int main()
{
  Parent *parent = new Parent();
  Child *child = new Child();

  Client *client1 = new Client(parent);
  Client *client2 = new Client(child);

  client1->takeValue();
  client2->takeValue();

  return 0;
}