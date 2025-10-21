#include<iostream>
#include<thread>
#include<chrono>
#include<ctime>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

class Vehicle {
  protected:
  int size;
  string vehicle_number;

  public:
  Vehicle(int size, string vehicle_number) : size(size), vehicle_number(vehicle_number) {}
  int getSize() {
    return size;
  };
  string getVehicleNumber() {
    return vehicle_number;
  }; 
};

class Car : public Vehicle {
  public:
  Car(string vehicle_number) : Vehicle(4, vehicle_number) {}
};

class Bike : public Vehicle {
  public:
  Bike(string vehicle_number) : Vehicle(2, vehicle_number) {}
};

class Truck : public Vehicle {
  public:
  Truck(string vehicle_number) : Vehicle(6, vehicle_number) {}
};

class ParkingSpot {
  protected:
  int size;
  string name;
  float price;
  Vehicle *vehicle;
  bool isOccupied;
  
  public:
  ParkingSpot(int size, string name, float price) : size(size), name(name), price(price), isOccupied(false) {}
  void toggleOccupancy() {
    isOccupied = !isOccupied;
  }
  virtual int getSize() {
    return size;
  };
  virtual string getName() {
    return name;
  };
  virtual float getPrice() {
    return price;
  };
  virtual Vehicle *getParkedVehicle() {
    return vehicle;
  };
  virtual bool checkOccupancy() {
    return isOccupied;
  }
};

class CompactParkingSpot : public ParkingSpot {
  public:
  CompactParkingSpot() : ParkingSpot(2, "Compact", 99.50) {}
};

class RegularParkingSpot : public ParkingSpot {
  public:
  RegularParkingSpot() : ParkingSpot(4, "Regular", 199.50) {}
};

class OversizeParkingSpot : public ParkingSpot {
  public:
  OversizeParkingSpot() : ParkingSpot(6, "Oversize", 299.50) {}
};

class TicketStrategy {
  protected:
  static int nextTicketId;
  int ticketId;
  Vehicle *vehicle;
  ParkingSpot *parkingSpot;
  int parkingSpotIdx;
  std::chrono::time_point<std::chrono::system_clock> entry_time;
  std::chrono::time_point<std::chrono::system_clock> exit_time;

  public:
  TicketStrategy(Vehicle *vehicle, ParkingSpot *parkingSpot, int parkingSpotIdx) {
    this->vehicle = vehicle;
    this->parkingSpot = parkingSpot;
    this->parkingSpotIdx = parkingSpotIdx;
    this->entry_time = std::chrono::system_clock::now();
    this->exit_time = entry_time;
    this->ticketId = ++nextTicketId;
  }
  int getTicketId() {
    return ticketId;
  }
  Vehicle *getVehicle() {
    return vehicle;
  }
  ParkingSpot *getParkingSpot() {
    return parkingSpot;
  }
  int getParkingSpotIdx() {
    return parkingSpotIdx;
  }
  auto getParkingEntryTime() {
    return entry_time;
  }
  auto getParkingExitTime() {
    return exit_time;
  }
  void setExitTime() {
    this->exit_time =  std::chrono::system_clock::now();
  }
  int getParkingDurationInMin() {
    return std::chrono::duration_cast<std::chrono::seconds> (exit_time - entry_time).count();
  }
  virtual float calculateFare() = 0;
  virtual void printTicket() = 0;
};

int TicketStrategy::nextTicketId = 0;

class BaseTicket : public TicketStrategy {
  public:
  BaseTicket(Vehicle *vehicle, ParkingSpot *parkingSpot, int parkingSpotIdx) : TicketStrategy(vehicle, parkingSpot, parkingSpotIdx) {}
  float calculateFare() override {
    int duration = getParkingDurationInMin();
    int hrs = duration/60;
    int mins = duration%60;
    float basePrice = parkingSpot->getPrice();
    return basePrice*hrs + (basePrice/60)*mins;
  }
  void printTicket() override {
    std::time_t entry_time_t = std::chrono::system_clock::to_time_t(entry_time);
    std::time_t exit_time_t = std::chrono::system_clock::to_time_t(exit_time);
    int duration = getParkingDurationInMin();
    int mins = duration/60;
    int secs = duration%60;
    cout<<"****************************"<<endl;
    cout<<"Ticket id: "<<ticketId<<endl;
    cout<<"Vehicle number: "<<vehicle->getVehicleNumber()<<endl;
    cout<<"Vehicle size: "<<vehicle->getSize()<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Parking type: "<<parkingSpot->getName()<<endl;
    cout<<"Parking size: "<<parkingSpot->getSize()<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Entry time: "<<std::ctime(&entry_time_t)<<endl;
    cout<<"Exit time: "<<std::ctime(&exit_time_t)<<endl;
    cout<<"Parking Duration: "<<mins<<" mins: "<<secs<<" secs"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Parking Fare: "<<calculateFare()<<endl;
    cout<<"****************************"<<endl;
  }
};

class PeakTicket : public TicketStrategy {
  public:
  PeakTicket(Vehicle *vehicle, ParkingSpot *parkingSpot, int parkingSpotIdx) : TicketStrategy(vehicle, parkingSpot, parkingSpotIdx) {}
  float calculateFare() override {
    int duration = getParkingDurationInMin();
    int hrs = duration/60;
    int mins = duration%60;
    float basePrice = parkingSpot->getPrice();
    return 2*(basePrice*hrs + (basePrice/60)*mins);
  }
  void printTicket() override {
    std::time_t entry_time_t = std::chrono::system_clock::to_time_t(entry_time);
    std::time_t exit_time_t = std::chrono::system_clock::to_time_t(exit_time);
    int duration = getParkingDurationInMin();
    int mins = duration/60;
    int secs = duration%60;
    cout<<"****************************"<<endl;
    cout<<"------Peak Time Ticket------"<<endl;
    cout<<"Ticket id: "<<ticketId<<endl;
    cout<<"Vehicle number: "<<vehicle->getVehicleNumber()<<endl;
    cout<<"Vehicle size: "<<vehicle->getSize()<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Parking type: "<<parkingSpot->getName()<<endl;
    cout<<"Parking size: "<<parkingSpot->getSize()<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Entry time: "<<std::ctime(&entry_time_t)<<endl;
    cout<<"Exit time: "<<std::ctime(&exit_time_t)<<endl;
    cout<<"Parking Duration: "<<mins<<" mins: "<<secs<<" secs"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Parking Fare: "<<calculateFare()<<endl;
    cout<<"****************************"<<endl;
  }
};

class TicketManager {
  unordered_map<Vehicle*, TicketStrategy*> ticket_list;
  static TicketManager *instance;

  TicketManager() {}

  public:
  static TicketManager *getInstance() {
    if(instance == nullptr) {
      instance = new TicketManager();
    }
    return instance;
  }
  TicketStrategy *createTicket(Vehicle *vehicle, ParkingSpot *parkingSpot, int parkingSpotIdx, string strategyType) {
    if(ticket_list.find(vehicle) != ticket_list.end()) {
      cout<<"Cannot create another tickt for parked vehicle"<<endl;
      return nullptr;
    }
    TicketStrategy *strategy;
    if(strategyType == "Base") {
      strategy = new BaseTicket(vehicle, parkingSpot, parkingSpotIdx);
    } else if(strategyType == "Peak") {
      strategy = new PeakTicket(vehicle, parkingSpot, parkingSpotIdx);
    } else {
      cout<<"Choose correct ticket type"<<endl;
      return nullptr;
    }
    ticket_list[vehicle] = strategy;
    return strategy;
  }
  void printTicket(Vehicle *vehicle, ParkingSpot *parkingSpot) {
    if(ticket_list.find(vehicle) == ticket_list.end()) {
      cout<<"No vehicle parked"<<endl;
      return;
    }
    auto ticket = ticket_list[vehicle];
    ticket_list.erase(vehicle);
    ticket->printTicket();
  }
};

TicketManager* TicketManager::instance = nullptr;

class ParkingManager {
  vector<ParkingSpot*> parkings;
  unordered_map<Vehicle*, pair<ParkingSpot*, int>> vehicle_parkings;
  TicketManager *ticketManager;
  static ParkingManager *instance;
  
  ParkingManager() {
    this->ticketManager = TicketManager::getInstance();
  }
  
  public:
  static ParkingManager *getInstance() {
    if(instance == nullptr) {
      instance = new ParkingManager();
    }
    return instance;
  }
  void addParking(ParkingSpot *parking) {
    parkings.push_back(parking);
  }
  void assignParking(Vehicle *vehicle, string ticketType) {
    if(vehicle_parkings.find(vehicle) != vehicle_parkings.end()) {
      cout<<"Vehicle already parked"<<endl;
      return;
    }
    bool flag = false;
    for(int i = 0 ; i < parkings.size() ; i++) {
      if(parkings[i]->getSize() == vehicle->getSize() && parkings[i]->checkOccupancy() == false) {
        TicketStrategy *ticket = ticketManager->createTicket(vehicle, parkings[i], i, ticketType);
        if(ticket == nullptr) break;
        flag = true;
        parkings[i]->toggleOccupancy();
        vehicle_parkings[vehicle] = make_pair(parkings[i], i);
        break;
      }
    }
    if(flag == true) {
      cout<<"Your vehicle with number: "<<vehicle->getVehicleNumber()<<" is parked at "<<vehicle_parkings[vehicle].second<< "location"<<endl;
    } else {
      cout<<"No parking found for your vehicle. Please wait for parking to be free"<<endl;
    }
  }
  void exitParking(Vehicle *vehicle) {
    if(vehicle_parkings.find(vehicle) == vehicle_parkings.end()) {
      cout<<"No vehicle parked with number "<<vehicle->getVehicleNumber()<<endl;
      return;
    }
    auto vehicle_location = vehicle_parkings[vehicle];
    ParkingSpot *parkingSpot = vehicle_location.first;
    int location = vehicle_location.second;
    parkings[location]->toggleOccupancy();
    vehicle_parkings.erase(vehicle);
    ticketManager->printTicket(vehicle, parkingSpot);
  }
};

ParkingManager *ParkingManager::instance = nullptr;


int main() {
  Vehicle *car1 = new Car("car1");
  Vehicle *car2 = new Car("car2");
  Vehicle *car3 = new Car("car3");
  Vehicle *bike1 = new Bike("bike1");
  Vehicle *bike2 = new Bike("bike2");
  Vehicle *truck1 = new Truck("truck1");

  ParkingSpot *compact1 = new CompactParkingSpot();
  ParkingSpot *compact2 = new CompactParkingSpot();
  ParkingSpot *regular1 = new RegularParkingSpot();
  ParkingSpot *regular2 = new RegularParkingSpot();
  ParkingSpot *oversize1 = new OversizeParkingSpot();
  ParkingSpot *oversize2 = new OversizeParkingSpot();

  ParkingManager *parkingManager = ParkingManager::getInstance();

  parkingManager->addParking(compact1);
  parkingManager->addParking(compact2);
  parkingManager->addParking(regular1);
  parkingManager->addParking(regular2);
  parkingManager->addParking(oversize1);
  parkingManager->addParking(oversize2);

  
  parkingManager->assignParking(bike1, "Base");
  std::this_thread::sleep_for(std::chrono::seconds(5));
  parkingManager->assignParking(bike2, "Peak");
  std::this_thread::sleep_for(std::chrono::minutes(1));
  parkingManager->assignParking(car1, "Peak");
  std::this_thread::sleep_for(std::chrono::seconds(20));
  parkingManager->assignParking(truck1, "Base");
  std::this_thread::sleep_for(std::chrono::seconds(30));
  parkingManager->exitParking(bike1);
  std::this_thread::sleep_for(std::chrono::minutes(2));
  parkingManager->exitParking(bike2);
  std::this_thread::sleep_for(std::chrono::seconds(10));
  parkingManager->assignParking(car2, "Base");
  std::this_thread::sleep_for(std::chrono::seconds(15));
  parkingManager->exitParking(truck1);
  std::this_thread::sleep_for(std::chrono::minutes(2));
  parkingManager->assignParking(car3, "Peak");
  std::this_thread::sleep_for(std::chrono::seconds(5));
  parkingManager->exitParking(car3);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  parkingManager->exitParking(car1);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  parkingManager->exitParking(car2);
  return 0;
}