#include <iostream>
using namespace std;

// A precondition should be satisfied before a method can be executed
// Sub classes can weaken the pre condition but cannot strengthen it

class User
{
  // Pre condition: Password must be 8 characters long
public:
  virtual void setPassword(string pass)
  {
    if (pass.size() < 8)
    {
      throw invalid_argument("Password must be 8 characters long");
    }
    cout << "Password set successfully" << endl;
  }
};

class AdminUser : public User
{
public:
  void setPassword(string pass) override
  {
    if (pass.size() < 6)
    {
      throw invalid_argument("Password must be 6 characters long");
    }
    cout << "Password set successfully" << endl;
  }
};

int main()
{
  User *user = new AdminUser();
  user->setPassword("1234567");

  return 0;
}