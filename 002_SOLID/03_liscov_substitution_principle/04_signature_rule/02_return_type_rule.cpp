#include <iostream>
using namespace std;

class Animal
{
  // methods for Animal
};

class Dog : public Animal
{
  // methods for Dog
};

class Parent
{
public:
  virtual Animal *getAnimal()
  {
    cout << "Parent: Returning Animal instance" << endl;
    return new Animal();
  }
};

class Child : public Parent
{
public:
  Dog *getAnimal() override
  {
    cout << "Child: Returning Dog instance" << endl;
    return new Dog();
  }
};

int main()
{
  Parent *parent = new Parent();
  Child *child = new Child();
  parent->getAnimal();
  child->getAnimal();

  return 0;
}