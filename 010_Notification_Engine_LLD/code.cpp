#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

// Notification abstract class
class Notification {
  public:
  virtual string getContent() = 0;
  
  virtual ~Notification() {}
};

// Notification Decorator class
class NotificationDecorator : public Notification {
  protected:
  Notification *decorator;

  public:
  NotificationDecorator(Notification *decorator) : decorator(decorator) {}
  
  virtual ~NotificationDecorator() {
    delete decorator;
  }
};

// Timestamp decorator class
class TimestampDecorator : public NotificationDecorator {
  public:
  TimestampDecorator(Notification *decorator) : NotificationDecorator(decorator) {}

  string getContent() override {
    return "[timestamp] " + decorator->getContent();
  }
};

// Signature decorator class
class SignatureDecorator : public NotificationDecorator {
  public:
  SignatureDecorator(Notification *decorator) : NotificationDecorator(decorator) {}

  string getContent() override {
    return "[signature] " + decorator->getContent();
  }
};

// Simple notification class
class SimpleNotification : public Notification {
  string content;
  
  public:
  SimpleNotification(const string &content) : content(content) {}
  
  string getContent() override {
    return content;
  }
};

// Observer abstract class
class Observer {
  public:
  virtual void update() = 0;

  virtual ~Observer() {}
};

// Observable abstract class
class Observable {
  public:
  virtual void addObserver(Observer *observer) = 0;
  virtual void removeObserver(Observer *observer) = 0;
  virtual void notifyObservers() = 0;
  virtual ~Observable() {}
};

// Notification observable concrete class
class NotificationObservable : public Observable {
  Notification *currentNotification;
  vector<Observer*> observers;
  public:
  NotificationObservable() {
    currentNotification = nullptr;
  }

  void addObserver(Observer *observer) override {
    observers.push_back(observer);
  }

  void removeObserver(Observer *observer) override {
    auto it = find(observers.begin(), observers.end(), observer);
    if(it != observers.end()) {
      observers.erase(it);
    }
  }

  void setNotification(Notification *notification) {
    if(currentNotification == nullptr) delete currentNotification;
    currentNotification = notification;
    notifyObservers();
  }

  void notifyObservers() override {
    for(auto observer : observers) {
      observer->update();
    }
  }

  Notification* getNotification() {
    return currentNotification;
  }

  string getNotificationContent() {
    return currentNotification->getContent();
  }

  ~NotificationObservable() {
    if(currentNotification != nullptr) {
      delete currentNotification;
    }
  }
};

// NotificationService class
class NotificationService {
  NotificationObservable *observable;
  vector<Notification*> notifications;
  static NotificationService *instance;

  NotificationService() {
    observable = new NotificationObservable;
  }

  public:
  static NotificationService* getInstance() {
    if(instance == nullptr) {
      instance = new NotificationService();
    }
    return instance;
  }

  NotificationObservable *getObservable() {
    return observable;
  }

  void sendNotification(Notification *notification) {
    notifications.push_back(notification);
    observable->setNotification(notification);
  }

  ~NotificationService() {
    delete observable;
  }
};

NotificationService *NotificationService::instance = nullptr;

// Logger observer class
class LoggerObserver : public Observer {
  NotificationObservable *observable;
  
  public:
  LoggerObserver() {
    observable = NotificationService::getInstance()->getObservable();
    observable->addObserver(this);
  }
  
  LoggerObserver(NotificationObservable *observable) : observable(observable) {
    observable->addObserver(this);
  }

  void update() override {
    cout<<"Logging new Notification: \n"<<observable->getNotificationContent()<<endl;
  }
};

// NotificationStrategy class
class NotificationStrategy {
  public:
  virtual void sendNotification(string content) = 0;
  virtual ~NotificationStrategy() {}
};

// EmailStrategy concrete class
class EmailStrategy : public NotificationStrategy {
  string emailId;

  public:
  EmailStrategy(string emailId) : emailId(emailId) {}
  
  void sendNotification(string content) override {
    cout<<"Sending email notification to: "<<emailId<<"\t"<<content<<endl;
  }
};

// SMSStrategy concrete class
class SMSStrategy : public NotificationStrategy {
  string mobileNumber;

  public:
  SMSStrategy(string mobileNumber) : mobileNumber(mobileNumber) {}
  
  void sendNotification(string content) override {
    cout<<"Sending SMS notification to: "<<mobileNumber<<"\t"<<content<<endl;
  }
};

// PopupStrategy concrete class
class PopupStrategy : public NotificationStrategy {

  public:
  
  void sendNotification(string content) override {
    cout<<"Sending popup notification:"<<"\t"<<content<<endl;
  }
};

// NotificationEngine observer class 
class NotificationEngineObserver : public Observer {
  NotificationObservable *observable;
  vector<NotificationStrategy*> strategies;
  
  public:
  NotificationEngineObserver() {
    observable = NotificationService::getInstance()->getObservable();
    observable->addObserver(this);
  }

  void addStrategy(NotificationStrategy *ns) {
    strategies.push_back(ns);
  }

  void update() override {
    string notification = observable->getNotificationContent();
    for(auto strategy : strategies) {
      strategy->sendNotification(notification);
    }
  }
};

int main() {
  // Notification service
  NotificationService *ns = NotificationService::getInstance();
  // Logger Observer
  LoggerObserver *lg = new LoggerObserver();
  // NotificationEngine observer
  NotificationEngineObserver *neo = new NotificationEngineObserver();

  neo->addStrategy(new EmailStrategy("random@gmail.com"));
  neo->addStrategy(new SMSStrategy("+911234567890"));
  neo->addStrategy(new PopupStrategy());

  // Notifications
  Notification *notification = new SimpleNotification("First notification");
  notification = new TimestampDecorator(notification);
  notification = new SignatureDecorator(notification);

  ns->sendNotification(notification);

  delete lg;
  delete neo;
  return 0;
}