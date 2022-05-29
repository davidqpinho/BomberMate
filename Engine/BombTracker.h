#ifndef __BOMB_TRACKER_H_
#define __BOMB_TRACKER_H_
#include <list>
#include <string>

using namespace std;

#define IDDLE   -1
#define SETBOMB 1
#define BOMBEXP 2

class IBombObserver {
 public:
  virtual ~IBombObserver(){};
  virtual void Update( int event) = 0;
};

class IBombSubject {
 public:
  //virtual ~ISubject(){};
  virtual void Attach(IBombObserver *observer) = 0;
  virtual void Detach(IBombObserver *observer) = 0;
  virtual void AddBombSet() = 0;
  virtual void RemoveBombSet() = 0;
  virtual void Notify(int event) = 0;
};

class BombSubject : public IBombSubject {
 public:
  
  virtual ~BombSubject();
  
  void Attach(IBombObserver *observer);

  void Detach(IBombObserver *observer);

  void Notify(int event) override;

  void AddBombSet() override;
  
  void RemoveBombSet() override;

  void CreateEvent(int event);

  int CanSpawnBombs(int playerBombs);

  void UpdateTimer();

  int bombsSet = 0;
  

 private:

  list<IBombObserver *> list_observer_;
  int bombTimer = 0;
};

class BombObserver : public IBombObserver {
 
 public:
  
  BombObserver(BombSubject &subject);
  
  virtual ~BombObserver() { }

  void Update( int event) override;

  void SetBomb(int column, int row);

  int  ReadEvent();

  int  GetEvent();

  void RemoveMeFromTheList(); 
  

 private:
  
  IBombSubject &subject_;
  int event = IDDLE;

};

#endif