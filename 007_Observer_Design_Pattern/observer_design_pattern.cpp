#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Abstract observer interface
class ISubscriber
{
public:
  virtual void update() = 0;
  virtual ~ISubscriber() {}
};

class IChannel
{
public:
  virtual void subscribe(ISubscriber *subscriber) = 0;
  virtual void unsubscribe(ISubscriber *subscriber) = 0;
  virtual void notifySubscriber() = 0;
  virtual ~IChannel() {}
};

class Channel : public IChannel
{
private:
  string name, latestVideo;
  vector<ISubscriber *> subscribers;

public:
  Channel(const string &name)
  {
    this->name = name;
  }
  void subscribe(ISubscriber *subscriber) override
  {
    // to avoide duplicates
    if (find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end())
    {
      subscribers.push_back(subscriber);
    }
  }
  void unsubscribe(ISubscriber *subscriber) override
  {
    auto it = find(subscribers.begin(), subscribers.end(), subscriber);
    if (it != subscribers.end())
    {
      subscribers.erase(it);
    }
  }
  void notifySubscriber() override
  {
    for (auto subscriber : subscribers)
    {
      subscriber->update();
    }
  }
  // upload new video and notify all subscribers
  void uploadVideo(const string &title)
  {
    latestVideo = title;
    cout << "\n[" << name << " uploaded \"" << title << "\"]\n";
    notifySubscriber();
  }
  string getVideoData()
  {
    return "Checkout our new Video: " + latestVideo + "\n";
  }
};

class Subscriber : public ISubscriber
{
private:
  string name;
  Channel *channel;

public:
  Subscriber(string name, Channel *channel)
  {
    this->name = name;
    this->channel = channel;
  }
  void update() override
  {
    cout << "Hey, " << name << ", " << this->channel->getVideoData();
  }
};

int main()
{
  Channel *channel = new Channel("Coder Army");
  Subscriber *sub1 = new Subscriber("Varun", channel);
  Subscriber *sub2 = new Subscriber("Tarun", channel);

  // varun and tarun susbcribe to the channel
  channel->subscribe(sub1);
  channel->subscribe(sub2);

  // uploading the video will send the notification to varun and tarun
  channel->uploadVideo("Observer Design Pattern");
  // varun unsubscribe to the channel
  channel->unsubscribe(sub1);
  // uploading the video will send the notification to tarun only
  channel->uploadVideo("Decorator Design Pattern");

  return 0;
}