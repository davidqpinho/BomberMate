#ifndef __PLAYER_OBSERVER_H_
#define __PLAYER_OBSERVER_H_
#include <list>
#include <string>

using namespace std;


class IPlayerObserver {
 public:
  virtual ~IPlayerObserver(){};
  virtual void Update( int event) = 0;
};

class IPlayerSubject {
 public:
  //virtual ~ISubject(){};
  virtual void Attach(IPlayerObserver *observer) = 0;
  virtual void Detach(IPlayerObserver *observer) = 0;
  virtual void Notify(int event) = 0;
};

class PlayerSubject : public IPlayerSubject {
 public:
  
  virtual ~PlayerSubject();
  
  void Attach(IPlayerObserver *observer);

  void Detach(IPlayerObserver *observer);

  void Notify(int event) override;

  void CreateEvent(int event);

 private:

  list<IPlayerObserver *> list_observer_;

};

class PlayerObserver : public IPlayerObserver {
 
 public:
  
  PlayerObserver(PlayerSubject &subject);
  
  virtual ~PlayerObserver() { }

  void Update( int event) override;

  void SetStatus(int life, int bombStrength, int speed, int column, int line);

  int  GetLife();

  int  GetBombStrength();

  int  GetSpeed();

  int  GetLine();

  int  GetColumn();

  int  ReadEvent();

  int  GetEvent();

  void RemoveMeFromTheList(); 
  

 private:
  
  IPlayerSubject &subject_;
  int event=-1;

};

#endif