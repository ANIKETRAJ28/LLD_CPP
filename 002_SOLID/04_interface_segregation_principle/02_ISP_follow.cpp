#include <iostream>
using namespace std;

class Shape2D
{
public:
  virtual double area() = 0;
};

class Shape3D
{
public:
  virtual double area() = 0;
  virtual double volume() = 0;
};

class Square : public Shape2D
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
};

class Rectangle : public Shape2D
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
};

class Cube : public Shape3D
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
  Shape2D *square = new Square(5);
  Shape2D *rectangle = new Rectangle(4, 5);
  Shape3D *cube = new Cube(5);
  cout << cube->area() << endl;
  cout << cube->volume() << endl;
  cout << square->area() << endl;
  cout << rectangle->area() << endl;

  return 0;
}