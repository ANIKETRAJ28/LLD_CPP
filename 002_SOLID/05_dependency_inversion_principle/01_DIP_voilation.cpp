#include <iostream>
using namespace std;

class saveToSQL
{
public:
  void save()
  {
    cout << "Saving to sql..." << endl;
  }
};

class saveToMongo
{
public:
  void save()
  {
    cout << "Saving to mongo..." << endl;
  }
};

class Application
{
private:
  saveToSQL sql;
  saveToMongo mongo;

public:
  void save()
  {
    sql.save();
    mongo.save();
  }
};

int main()
{
  Application *application = new Application();
  application->save();

  return 0;
}