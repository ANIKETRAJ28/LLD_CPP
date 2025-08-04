#include <iostream>
#include <vector>
using namespace std;

class Product
{
public:
  string name;
  double price;

  Product(string name, double price)
  {
    this->price = price;
    this->name = name;
  }
};

// ShoppingCart only responsible for cart related business logic
class ShoppingCart
{
private:
  vector<Product *> products;

public:
  void addProduct(Product *p)
  {
    products.push_back(p);
  }

  // gets the groducts in the cart
  const vector<Product *> &getProducts()
  {
    return products;
  }

  // calculate total price in the cart
  double calcuateTotal()
  {
    double total = 0;
    for (auto p : products)
    {
      total += p->price;
    }
    return total;
  }
};

// ShoppingCartPrinter only responsible for printing invoices
class ShoppingCartPrinter
{
private:
  ShoppingCart *cart;

public:
  ShoppingCartPrinter(ShoppingCart *cart)
  {
    this->cart = cart;
  }

  void printInvoice()
  {
    cout << "Shopping cart invoice\n";
    for (auto p : cart->getProducts())
    {
      cout << p->name << " - $" << p->price << endl;
    }
    cout << "Total: $" << cart->calcuateTotal() << endl;
  }
};

// ShoppingCartStorage is an abstrat class which can be used bu different storage classes which do not alter the class signature
class ShoppingCartStorage
{
private:
  ShoppingCart *cart;

public:
  virtual void save(ShoppingCart *cart) = 0;
};

// SQL storage logic
class SaveToSQL : public ShoppingCartStorage
{
public:
  void save(ShoppingCart *cart) override
  {
    cout << "Saving shopping cart to sql database..." << endl;
  }
};

// Mongo storage logic
class SaveToMongo : public ShoppingCartStorage
{
public:
  void save(ShoppingCart *cart) override
  {
    cout << "Saving shopping cart to mongo database..." << endl;
  }
};

// File storage logic
class SaveToFile : public ShoppingCartStorage
{
public:
  void save(ShoppingCart *cart) override
  {
    cout << "Saving shopping cart to file storage..." << endl;
  }
};

int main()
{
  ShoppingCart *cart = new ShoppingCart();

  cart->addProduct(new Product("Laptop", 1500));
  cart->addProduct(new Product("Mouse", 50));

  ShoppingCartPrinter *printer = new ShoppingCartPrinter(cart);
  printer->printInvoice();

  ShoppingCartStorage *sql = new SaveToSQL();
  ShoppingCartStorage *mongo = new SaveToMongo();
  ShoppingCartStorage *file = new SaveToFile();
  sql->save(cart);   // Save to SQL database
  mongo->save(cart); // Save to mongo database
  file->save(cart);  // Save to file storage

  return 0;
}