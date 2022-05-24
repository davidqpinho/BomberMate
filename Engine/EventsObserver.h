#ifndef __EVENTS_OBSERVER_H_
#define __EVENTS_OBSERVER_H_
#include <list>
#include <string>

using namespace std;

class IObserver {
 public:
  virtual ~IObserver(){};
  virtual void Update(int event) = 0;
};

class ISubject {
 public:
  //virtual ~ISubject(){};
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify(int event) = 0;
};

/**
 * The Subject owns some important state and notifies observers when the state
 * changes.
 */

class Subject : public ISubject {
 public:
  
  //virtual ~Subject();
  
  void Attach(IObserver *observer);

  void Detach(IObserver *observer);

  void Notify(int event) override;

  void CreateEvent(int event);

 private:

  list<IObserver *> list_observer_;

};


class Observer : public IObserver {
 
 public:
  
  Observer(Subject &subject);
  
  virtual ~Observer() { }

  void Update(int event) override;

  int ReadEvent();

  int GetEvent();

  void RemoveMeFromTheList(); 

 private:
  
  Subject &subject_;
  static int static_number_;
  int event = -1;

};

#endif