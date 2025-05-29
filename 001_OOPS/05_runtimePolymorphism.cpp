#include <iostream>
#include <string>
using namespace std;

class Car
{
protected:
  string brand;
  string model;
  bool isEngineOn;
  int currentSpeed;

public:
  Car(string brand, string model)
  {
    this->brand = brand;
    this->model = model;
    this->isEngineOn = false;
    this->currentSpeed = 0;
  }

  // Common methods for All cars.
  void startEngine()
  {
    isEngineOn = true;
    cout << brand << " " << model << " : engine started." << endl;
  }

  void stopEngine()
  {
    isEngineOn = false;
    currentSpeed = 0;
    cout << brand << " " << model << " : engine turned off." << endl;
  }

  virtual void accelerate() = 0; // Abstract method for Dynamic Polymorphism
  virtual void brake() = 0;      // Abstract method for Dynamic Polymorphism
  virtual ~Car() {}              // Virtual destructor
};

class ManualCar : public Car
{
private:
  int currentGear;

public:
  ManualCar(string brand, string model) : Car(brand, model)
  {
    this->currentGear = 0;
  }

  // Specialized method for Manual Car
  void shiftGear(int gear)
  {
    currentGear = gear;
    cout << brand << " " << model << " : shifted to gear " << currentGear << endl;
  }

  // Overriding accelerate - Dynamic Polymorphism
  void accelerate()
  {
    if (!isEngineOn)
    {
      cout << brand << " " << model << " : cannot accelerate! engine is off." << endl;
      return;
    }
    currentSpeed += 20;
    cout << brand << " " << model << " : accelerating to " << currentSpeed << " km/h" << endl;
  }

  // Overriding brake - Dynamic Polymorphism
  void brake()
  {
    currentSpeed -= 20;
    if (currentSpeed < 0)
      currentSpeed = 0;
    cout << brand << " " << model << " : braking! speed is now " << currentSpeed << " km/h" << endl;
  }
};

class ElectricCar : public Car
{
private:
  int batteryLevel;

public:
  ElectricCar(string brand, string model) : Car(brand, model)
  {
    this->batteryLevel = 100;
  }

  // specialized method for Electric Car
  void chargeBattery()
  {
    batteryLevel = 100;
    cout << brand << " " << model << " : battery fully charged!" << endl;
  }

  // Overriding accelerate - Dynamic Polymorphism
  void accelerate()
  {
    if (!isEngineOn)
    {
      cout << brand << " " << model << " : cannot accelerate! engine is off." << endl;
      return;
    }
    if (batteryLevel <= 0)
    {
      cout << brand << " " << model << " : battery dead! cannot accelerate." << endl;
      return;
    }
    batteryLevel -= 10;
    currentSpeed += 15;
    cout << brand << " " << model << " : accelerating to " << currentSpeed << " km/h. Battery at " << batteryLevel << "%." << endl;
  }

  // Overriding brake - Dynamic Polymorphism
  void brake()
  {
    currentSpeed -= 15;
    if (currentSpeed < 0)
      currentSpeed = 0;
    cout << brand << " " << model << " : regenerative braking! speed is now " << currentSpeed << " km/h. Battery at " << batteryLevel << "%." << endl;
  }
};

// Main function
int main()
{
  Car *myManualCar = new ManualCar("Suzuki", "WagonR");
  myManualCar->startEngine();
  myManualCar->accelerate();
  myManualCar->accelerate();
  myManualCar->brake();
  myManualCar->stopEngine();

  cout << "----------------------" << endl;

  Car *myElectricCar = new ElectricCar("Tesla", "Model S");
  myElectricCar->startEngine();
  myElectricCar->accelerate();
  myElectricCar->accelerate();
  myElectricCar->brake();
  myElectricCar->stopEngine();

  // Cleanup
  delete myManualCar;
  delete myElectricCar;

  return 0;
}