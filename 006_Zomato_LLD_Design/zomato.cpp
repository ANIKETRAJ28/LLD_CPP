#include<iostream>
#include<vector>
#include<string>
using namespace std;

// Item class
class Item {
  protected:
  string name;
  float price;
  
  public:
  Item(string name, float price) : name(name), price(price) {}
  
  string getName() {
    return name;
  }
  
  float getPrice() {
    return price;
  }
};

// Restaurant class
class Restaurant {
  string name;
  string location;
  vector<Item*> dish;

  public:
  Restaurant(string location, string name) : location(location), name(name) {}
  string getLocation() {
    return location;
  }
  
  string getName() {
    return name;
  }

  void addDish(Item *item) {
    dish.push_back(item);
  }
  
  vector<Item*> getDishes() {
    return dish;
  }
  
  Item *getDish(string name) {
    for(auto item : dish) {
      if(item->getName() == name) {
        return item;
      }
    }
    return nullptr;
  }
};

// RestaurantManager (singleton) class
class RestaurantManager {
  vector<Restaurant*> restaurants;
  static RestaurantManager *instance;
  RestaurantManager() {}

  public:
  static RestaurantManager *getInstance() {
    if(instance == nullptr) {
      instance = new RestaurantManager();
    }
    return instance;
  }

  Restaurant *getRestaurantForLocation(string location) {
    for( Restaurant *res : restaurants) {
      if(res->getLocation() == location) {
        return res;
      }
    }
    return nullptr;
  }

  void addRestaurant(Restaurant *restaurant) {
    restaurants.push_back(restaurant);
  }
};

// CartItem class
class CartItem {
  Item *item;
  Restaurant *restaurant;

  public:
  CartItem(Item *item, Restaurant *restaurant) : item(item), restaurant(restaurant) {}
  Item *getItem() {
    return item;
  }

  Restaurant *getRestaurant() {
    return restaurant;
  }
};

// Cart class
class Cart {
  vector<CartItem*> items;
  
  public:
  void addItem(Item *item, Restaurant *restaurant) {
    items.push_back(new CartItem(item, restaurant));
  }
  void clearCart() {
    items.clear();
  }
  vector<CartItem*> getCartItems() {
    return items;
  }
};

// User class
class User {
  static int nextUserId;
  int id;
  string name;
  Cart *cart;

  public:
  User(string name) : name(name), id(++nextUserId) {
    cart = new Cart();
  }

  int getUserId() {
    return id;
  }

  string getName() {
    return name;
  }

  Cart *getCart() {
    return cart;
  }
};

// OrderFactory (abstract) class
class OrderFactory {
  public:
  virtual void dispatchOrder() = 0;
};

// SheduledOrder (OrderFactory concrete) class
class SheduledOrder : public OrderFactory {
  public:
  void dispatchOrder() override {
    cout<<"Your order is sheduled"<<endl;
  }
};

// CurrentOrder (OrderFactory concrete) class
class CurrentOrder : public OrderFactory {
  public:
  void dispatchOrder() override {
    cout<<"Your order is prepared"<<endl;
  }
};

// PaymentStrategy (abstract strategy) class 
class PaymentStrategy {
  public:
  virtual void pay(float amount) = 0;
};

// UPI (PaymentStrategy strategy) class
class UPI : public PaymentStrategy {
  public:
  void pay(float amount) override {
    cout<<"Payment done with upi of amount: "<<amount<<endl;
  }
};

// Card (PaymentStrategy strategy) class
class Card : public PaymentStrategy {
  public:
  void pay(float amount) override {
    cout<<"Payment done with card of amount: "<<amount<<endl;
  }
};

// NotificationStrategy (abstract strategy) class 
class NotificationStrategy {
  public:
  virtual void notify(User *user) = 0;
};

// SMS (NotificationStrategy strategy) class
class SMS : public NotificationStrategy {
  public:
  void notify(User *user) override {
    auto cart = user->getCart()->getCartItems();
    float total = 0;
    cout<<"SMS notification sent"<<endl;
    cout<<"---------Order summary---------"<<endl;
    for(int i = 0 ; i < cart.size() ; i++) {
      cout<<"Item: "<<i+1<<endl;
      cout<<"\tPrice: "<<" $"<<cart[i]->getItem()->getPrice()<<endl;
      cout<<"\tName: "<<cart[i]->getItem()->getName()<<endl;
      cout<<"\tRestaurant: "<<cart[i]->getRestaurant()->getName()<<endl;
      total += cart[i]->getItem()->getPrice();
      cout<<"*****************************"<<endl;
    }
    cout<<"---------Total: "<<total<<"---------"<<endl;
  }
};

// Email (NotificationStrategy strategy) class
class Email : public NotificationStrategy {
  public:
  void notify(User *user) override {
    auto cart = user->getCart()->getCartItems();
    float total = 0;
    cout<<"Email notification sent"<<endl;
    cout<<"---------Order summary---------"<<endl;
    for(int i = 0 ; i < cart.size() ; i++) {
      cout<<"Item: "<<i+1<<endl;
      cout<<"\tPrice: "<<" $"<<cart[i]->getItem()->getPrice()<<endl;
      cout<<"\tName: "<<cart[i]->getItem()->getName()<<endl;
      cout<<"\tRestaurant: "<<cart[i]->getRestaurant()->getName()<<endl;
      total += cart[i]->getItem()->getPrice();
      cout<<"*****************************"<<endl;
    }
    cout<<"---------Total: "<<total<<"---------"<<endl;
  }
};

// Order (abstract) class
class Order {
  protected:
  Restaurant *restaurant;
  Item *item;
  User *user;
  PaymentStrategy *ps;
  NotificationStrategy *ns;

  public:
  Order(User *user, PaymentStrategy *ps, NotificationStrategy *ns) : user(user), ps(ps), ns(ns) {}
  virtual void placeOrder(OrderFactory *of) = 0;
};

// PickOrder class
class PickUpOrder : public Order {
  public:
  PickUpOrder(User *user, PaymentStrategy *ps, NotificationStrategy *ns) : Order(user, ps, ns) {}
  
  void placeOrder(OrderFactory *of) override {
    float amount = 0;
    auto cart = user->getCart()->getCartItems();
    for(int i = 0 ; i < cart.size() ; i++) {
      amount += cart[i]->getItem()->getPrice();
    }
    cout<<"Your order has been placed successfully."<<endl;
    of->dispatchOrder();
    ps->pay(amount);
    ns->notify(user);
    user->getCart()->clearCart();
  }
};

// PickOrder class
class DeliveryOrder : public Order {
  public:
  DeliveryOrder(User *user, PaymentStrategy *ps, NotificationStrategy *ns) : Order(user, ps, ns) {}

  void placeOrder(OrderFactory *of) override {
    float amount = 0;
    auto cart = user->getCart()->getCartItems();
    for(int i = 0 ; i < cart.size() ; i++) {
      amount += cart[i]->getItem()->getPrice();
    }
    cout<<"Your order has been placed successfully."<<endl;
    of->dispatchOrder();
    ps->pay(amount);
    ns->notify(user);
    user->getCart()->clearCart();
  }
};

// OrderManager (singleton) class
class OrderManager {
  OrderManager() {}
  static OrderManager *instance;
  public:
  static OrderManager *getInstace() {
    if(instance == nullptr) {
      instance = new OrderManager();
    }
    return instance;
  }
  void pickupOrder(User *user, OrderFactory *of, PaymentStrategy *ps, NotificationStrategy *ns) {
    (new PickUpOrder(user, ps, ns))->placeOrder(of);
  }

  void deliveryOrder(User *user, OrderFactory *of, PaymentStrategy *ps, NotificationStrategy *ns) {
    (new DeliveryOrder(user, ps, ns))->placeOrder(of); 
  }
};

// Zomato (Orchestration singelton) class
class Zomato {
  OrderManager *om;
  RestaurantManager *rm;
  OrderFactory *so, *co;
  static Zomato *instance;
  Zomato(OrderManager *om, RestaurantManager *rm, SheduledOrder *so, CurrentOrder *co): om(om), rm(rm), so(so), co(co) {}

  public:
  static Zomato *getInstance(OrderManager *om, RestaurantManager *rm, SheduledOrder *so, CurrentOrder *co) {
    if(instance == nullptr) {
      instance = new Zomato(om, rm, so, co);
    }
    return instance;
  }

  void addRestaurant(Restaurant *res) {
    rm->addRestaurant(res);
  }

  Restaurant *searchRestaurant(string location) {
    return rm->getRestaurantForLocation(location);
  }

  void scheduleDeliveryOrder(User *user, PaymentStrategy *ps, NotificationStrategy *ns) {
    om->deliveryOrder(user, so, ps, ns);
  }

  void currentDeliveryOrder(User *user, PaymentStrategy *ps, NotificationStrategy *ns) {
    om->deliveryOrder(user, co, ps, ns);
  }

  void scheduledPickUpOrder(User *user, PaymentStrategy *ps, NotificationStrategy *ns) {
    om->pickupOrder(user, so, ps, ns);
  }

  void currentPickUpOrder(User *user, PaymentStrategy *ps, NotificationStrategy *ns) {
    om->pickupOrder(user, co, ps, ns);
  }
};


int User::nextUserId = 0;
RestaurantManager* RestaurantManager::instance = nullptr;
OrderManager* OrderManager::instance = nullptr;
Zomato* Zomato::instance = nullptr;

int main() {
  PaymentStrategy *upi = new UPI();
  PaymentStrategy *card = new Card();
  NotificationStrategy *email = new Email();
  NotificationStrategy *sms = new SMS();
  RestaurantManager *rm = RestaurantManager::getInstance();
  OrderManager *om = OrderManager::getInstace();
  SheduledOrder *so = new SheduledOrder();
  CurrentOrder *co = new CurrentOrder();
  Zomato *zomato = Zomato::getInstance(om, rm, so, co);
  Restaurant *res1 = new Restaurant("Pari Chowk", "Sagar Ratna");
  Restaurant *res2 = new Restaurant("Alpha", "UP 16 Dhaba");
  zomato->addRestaurant(res1);
  zomato->addRestaurant(res2);
  User *user1 = new User("Jon");
  User *user2 = new User("Bob");
  
  res1->addDish(new Item("Paneer", 350.95));
  res1->addDish(new Item("Naan", 30.50));
  res2->addDish(new Item("Biryani", 200.50));
  res2->addDish(new Item("Manchurian", 290.30));
  res2->addDish(new Item("Dosa", 150.00));
  res2->addDish(new Item("Mix Veg", 250.45));
  
  Restaurant *restaurant1 = zomato->searchRestaurant("Pari Chowk");
  Restaurant *restaurant2 = zomato->searchRestaurant("Alpha");
  Item *item1 = restaurant1->getDish("Paneer");
  Item *item2 = restaurant1->getDish("Naan");
  Item *item3 = restaurant2->getDish("Biryani");

  user1->getCart()->addItem(item1, restaurant1);
  user1->getCart()->addItem(item2, restaurant1);
  user2->getCart()->addItem(item3, restaurant2);

  zomato->currentPickUpOrder(user1, upi, email);
  zomato->scheduleDeliveryOrder(user2, card, sms);

  delete upi;
  delete sms;
  delete email;
  delete sms;
  delete user1;
  delete user2;
  delete item1;
  delete item2;
  delete item3;
  delete res1;
  delete res2;
  delete zomato;

  return 0;
}