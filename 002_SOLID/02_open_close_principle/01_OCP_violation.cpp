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

// Voilation of OCP: ShoppingCartStorage is modifing the class signature
class ShoppingCartStorage
{
private:
  ShoppingCart *cart;

public:
  ShoppingCartStorage(ShoppingCart *cart)
  {
    this->cart = cart;
  }

  void saveToSQLDB()
  {
    cout << "Saving shopping cart to sql database..." << endl;
  }

  void saveToMongoDB()
  {
    cout << "Saving shopping cart to mongo database..." << endl;
  }

  void saveToFile()
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

  ShoppingCartStorage *db = new ShoppingCartStorage(cart);
  db->saveToSQLDB();
  db->saveToMongoDB();
  db->saveToFile();

  return 0;
}