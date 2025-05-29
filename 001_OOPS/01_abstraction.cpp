#include <iostream>
#include <string>
using namespace std;

/*Abstract Class*/
/**
 * 1. This abstract class 'Car' defines some set of 'features' which every car should have
 * 2. The abstract class tells 'WHAT' all it can do rather than 'HOW' it does
 * 3. Since it is an abstract class, we cannot create the object of this class directly
 * 4. We need to inherit the class and then the child class will provide the implementation
 *    to this class 'features' or abstract (virtual) methods
 *
 * 5. In the real world a car has the given things to operate, which are represented in the class 'Car'
 * 6. As the user (us), we don't need to know the internal working of how these features
 *    (brake, accelerate, start enginer, turn off enginer) are working. But even if we know its not a problem
 * 7. They are hidden, and work under the hood
 * 8. Abstraction: Abstraction is hiding the internal implementation and just showing the necessary information to the end user
 */

class Car
{
public:
  virtual void startEngine() = 0;
  virtual void shiftGear(int gear) = 0;
  virtual void accelerate() = 0;
  virtual void brake() = 0;
  virtual void stopEngine() = 0;
  virtual ~Car() {}
};

/**
 * 1. The above abstract class 'Car' is the concrete definition of the car
 * 2. Now any car can be made using the defined features of the 'Car' class
 * 3. So, we create a sports car. This sports car will have its own features like brand and the model
 * 4. It will have its own custom implementation for the parent features (brake, accelerate, start enginer, turn off enginer),
 *    just like the real world where different cars can have different ways to accelerate, start engine etc.
 */

class SportsCar : public Car
{
public:
  string brand;
  string model;
  bool isEngineOn;
  int currentSpeed;
  int currentGear;

  SportsCar(string brand, string model)
  {
    this->brand = brand;
    this->model = model;
    isEngineOn = false;
    currentSpeed = 0;
    currentGear = 0;
  }

  // implementation of virtual functions
  void startEngine()
  {
    isEngineOn = true;
    cout << brand << " " << model << " " << " : engine started" << endl;
  }

  void shiftGear(int gear)
  {
    if (!isEngineOn)
    {
      cout << brand << " " << model << " : engine is off! cannot shift gear." << endl;
      return;
    }
    currentGear = gear;
    cout << brand << " " << model << " : shifted to gear " << currentGear << endl;
  }

  void accelerate()
  {
    if (!isEngineOn)
    {
      cout << brand << " " << model << " : engine is off! Cannot accelerate." << endl;
      return;
    }
    currentSpeed += 20; // hardcoding the speed value
    cout << brand << " " << model << " : accelerating to " << currentSpeed << " km/h" << endl;
  }

  void brake()
  {
    currentSpeed -= 20;
    if (currentSpeed < 0)
      currentSpeed = 0;
    cout << brand << " " << model << " : braking! speed is now " << currentSpeed << " km/h" << endl;
  }

  void stopEngine()
  {
    isEngineOn = false;
    currentGear = 0;
    currentSpeed = 0;
    cout << brand << " " << model << " : engine turned off." << endl;
  }
};

int main()
{
  Car *myCar = new SportsCar("Ford", "Mustang");

  myCar->startEngine();
  myCar->shiftGear(1);
  myCar->accelerate();
  myCar->shiftGear(2);
  myCar->accelerate();
  myCar->brake();
  myCar->stopEngine();

  delete myCar;

  return 0;
}