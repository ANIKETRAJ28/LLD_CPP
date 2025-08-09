#include <iostream>
using namespace std;

class DB
{
public:
  virtual void save() = 0;
};

class SQL : public DB
{
public:
  void save() override
  {
    cout << "Saving to sql..." << endl;
  }
};

class Mongo : public DB
{
public:
  void save() override
  {
    cout << "Saving to mongo..." << endl;
  }
};

class Application
{
private:
  DB *db;

public:
  Application(DB *db)
  {
    this->db = db;
  }
  void save()
  {
    db->save();
  }
};

int main()
{
  Application *application = new Application(new SQL());
  application->save();

  return 0;
}