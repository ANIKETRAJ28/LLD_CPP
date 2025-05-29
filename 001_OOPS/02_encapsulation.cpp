#include <iostream>
#include <string>
using namespace std;

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

/*Encapsulation*/
/**
 * Encapsulation says 2 things
 * 1. The objects variables and functions are wrapped or encapsulated together in a single unit called class
 * 2. It provides data security, my not giving direct access to modify the variables and providing getters and setters
 * Taking 2nd point in mind, there are access modifiers (public, private, protected) that provides the data security
 */

class SportsCar : public Car
{
  string brand;
  string model;
  bool isEngineOn;
  int currentSpeed;
  int currentGear;
  // Introduce new variable to explain setters
  string tyreCompany;

public:
  SportsCar(string brand, string model)
  {
    this->brand = brand;
    this->model = model;
    isEngineOn = false;
    currentSpeed = 0;
    currentGear = 0;
    tyreCompany = "MRF";
  }

  int getSpeed()
  {
    return currentSpeed;
  }

  string getTyreCompany()
  {
    return tyreCompany;
  }

  void setTyreCompany(string tyreCompany)
  {
    // we can add validations to setter, hence provide data security
    this->tyreCompany = tyreCompany;
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
  SportsCar *myCar = new SportsCar("Ford", "Mustang");

  myCar->startEngine();
  myCar->shiftGear(1);
  myCar->accelerate();
  myCar->shiftGear(2);
  myCar->accelerate();
  myCar->brake();
  myCar->stopEngine();

  // Setting arbitrary value to speed is not possible
  //  mySportsCar->currentSpeed = 500;

  // This will give error as currentSpeed is not directly accessible
  // cout << "Current Speed of My Sports Car is set to " << mySportsCar->currentSpeed << endl;
  cout << "Current speed of my sports Car is " << myCar->getSpeed() << endl;

  delete myCar;

  return 0;
}