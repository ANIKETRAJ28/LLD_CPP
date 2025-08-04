#include <iostream>
using namespace std;

class Car
{
protected:
  int speed;

public:
  Car()
  {
    speed = 0;
  }
  void accelerate()
  {
    cout << "Accelerating" << endl;
    speed += 20;
  }
  virtual void brake()
  {
    cout << "Applying brakes in Car" << endl;
    speed -= 20;
  }
};

class HybridCar : public Car
{
private:
  int charge;

public:
  HybridCar() : Car()
  {
    charge = 0;
  }
  void brake() override
  {
    cout << "Applying brakes in Hybrid Car" << endl;
    speed -= 20;
    charge += 20;
  }
};

int main()
{
  Car *hybridCar = new HybridCar();
  hybridCar->accelerate();
  hybridCar->brake();

  return 0;
}