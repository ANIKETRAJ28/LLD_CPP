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

// Voilation of SRP: ShoppingCart is handling multiple responsibilities
class ShoppingCart
{
private:
  vector<Product *> products;

public:
  void addProduct(Product *p)
  {
    products.push_back(p);
  }

  const vector<Product *> &getProducts()
  {
    return products;
  }

  // 1. Calculates total price in the cart
  double calculateTotal()
  {
    double total = 0;
    for (auto p : products)
    {
      total += p->price;
    }
    return total;
  }

  // 2. Prints the invoice
  void printInvoice()
  {
    cout << "Shopping Cart invoice:\n";
    for (auto p : products)
    {
      cout << p->name << " - $" << p->price << endl;
    }
    cout << "Total: $" << calculateTotal() << endl;
  }

  // 3. Save to DB
  void saveToDB()
  {
    cout << "Saving to DB..." << endl;
  }
};

int main()
{
  ShoppingCart *cart = new ShoppingCart();

  cart->addProduct(new Product("Laptop", 1500));
  cart->addProduct(new Product("Mouse", 50));

  cart->printInvoice();
  cart->saveToDB();

  return 0;
}
