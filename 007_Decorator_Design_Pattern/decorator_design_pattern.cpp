#include<iostream>
#include<string>
using namespace std;

// Base class for mario and power-up decorators
class Character {
  public:
  virtual string getAbilities() = 0;
  virtual ~Character() {}
};

// Base form mario class
class Mario : public Character {
  public:
  string getAbilities() override {
    return "Mario with";
  }
};

// Decorator class for power-up
class Decorator : public Character {
  protected:
  Character *character;
  public:
  Decorator(Character *c) : character(c) {}
};

// Height-up decorator class
class HeightUp : public Decorator {
  public:
  HeightUp(Character *c) : Decorator(c) {}
  string getAbilities() override {
    return character->getAbilities() + " height ability";
  }
};

// Gun-power decorator class
class GunPower : public Decorator {
  public:
  GunPower(Character *c) : Decorator(c) {}
  string getAbilities() override {
    return character->getAbilities() + " gun ability";
  }
};

// Star-power decorator class
class StarPower : public Decorator {
  public:
  StarPower(Character *c) : Decorator(c) {}
  string getAbilities() override {
    return character->getAbilities() + " star ability";
  }
};


int main() {
  Character *star_mario = new StarPower(new Mario());
  Character *gun_height_mario = new HeightUp(new GunPower(new Mario()));
  Character *gun_star_height_mario = new HeightUp(new StarPower(new GunPower(new Mario)));
  cout<<star_mario->getAbilities()<<endl;
  cout<<gun_height_mario->getAbilities()<<endl;
  cout<<gun_star_height_mario->getAbilities()<<endl;
  delete star_mario;
  delete gun_height_mario;
  delete gun_star_height_mario;
  return 0;
}