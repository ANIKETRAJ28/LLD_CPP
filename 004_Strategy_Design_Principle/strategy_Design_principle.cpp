#include <iostream>
using namespace std;

// stratergy class for walk
class WalkableRobot
{
public:
  virtual void walk() = 0;
  virtual ~WalkableRobot() {}
};
// concrete class for walk
class NormalWalk : public WalkableRobot
{
public:
  void walk() override
  {
    cout << "Walking normally..." << endl;
  }
};
// concrete class for walk
class NoWalk : public WalkableRobot
{
public:
  void walk() override
  {
    cout << "Cannot walk..." << endl;
  }
};
// stratergy class for talk
class TalkableRobot
{
public:
  virtual void talk() = 0;
  virtual ~TalkableRobot() {}
};

// concrete class for talk
class NormalTalk : public TalkableRobot
{
public:
  void talk() override
  {
    cout << "Talking normally..." << endl;
  }
};
// concrete class for talk
class NoTalk : public TalkableRobot
{
public:
  void talk() override
  {
    cout << "Cannot talk..." << endl;
  }
};
// stratergy class for fly
class FlyableRobot
{
public:
  virtual void fly() = 0;
  virtual ~FlyableRobot() {}
};

// concrete class for fly
class NormalFly : public FlyableRobot
{
public:
  void fly() override
  {
    cout << "Normal fly..." << endl;
  }
};

// concrete class for fly
class NoFly : public FlyableRobot
{
public:
  void fly() override
  {
    cout << "Cannot fly..." << endl;
  }
};

// Robot base class
class Robot
{
protected:
  WalkableRobot *walkableBehavior;
  TalkableRobot *talkableBehavior;
  FlyableRobot *flyableBehavior;

public:
  Robot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f)
  {
    this->walkableBehavior = w;
    this->talkableBehavior = t;
    this->flyableBehavior = f;
  }
  void walk()
  {
    walkableBehavior->walk();
  }
  void talk()
  {
    talkableBehavior->talk();
  }
  void fly()
  {
    flyableBehavior->fly();
  }
  virtual void projection() = 0; // Abstract method for sub class
};

class CompanionRobot : public Robot
{
public:
  CompanionRobot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f) : Robot(w, t, f) {};
  void projection() override
  {
    cout << "Display friendly companion features..." << endl;
  }
};

class WorkerRobot : public Robot
{
public:
  WorkerRobot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f) : Robot(w, t, f) {};
  void projection() override
  {
    cout << "Display worker efficiency stats..." << endl;
  }
};

int main()
{
  Robot *robot1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly());
  robot1->walk();
  robot1->talk();
  robot1->fly();
  robot1->projection();

  cout << "-----------------\n";

  Robot *robot2 = new WorkerRobot(new NoWalk(), new NoTalk(), new NormalFly());
  robot2->walk();
  robot2->talk();
  robot2->fly();
  robot2->projection();
  return 0;
}