#include <iostream>
using namespace std;

class Shape
{
public:
  virtual double area() = 0;
  virtual double volume() = 0;
};

class Square : public Shape
{
private:
  double side;

public:
  Square(double side)
  {
    this->side = side;
  }
  double area() override
  {
    return side * side;
  }

  double volume() override
  {
    throw logic_error("Volume not applicable for Square");
  }
};

class Rectangle : public Shape
{
private:
  double length, breadth;

public:
  Rectangle(double length, double breadth)
  {
    this->length = length;
    this->breadth = breadth;
  }
  double area() override
  {
    return length * breadth;
  }

  double volume() override
  {
    throw logic_error("Volume not applicable for Rectangle");
  }
};

class Cube : public Shape
{
private:
  double side;

public:
  Cube(double side)
  {
    this->side = side;
  }
  double area() override
  {
    return 6 * side * side;
  }

  double volume() override
  {
    return side * side * side;
  }
};

int main()
{
  Shape *square = new Square(5);
  Shape *rectangle = new Rectangle(4, 5);
  Shape *cube = new Cube(5);
  cout << cube->area() << endl;
  cout << cube->volume() << endl;
  cout << square->area() << endl;
  cout << square->volume() << endl;
  cout << rectangle->area() << endl;
  cout << rectangle->volume() << endl;

  return 0;
}