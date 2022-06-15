#ifndef __MOVEMENT_STATE_H_
#define __MOVEMENT_STATE_H_

#include <stdio.h>
#include "Component.h"

/*State*/
#define IDDLE                                           -1
#define TURN                                            0
#define WALKING_LEFT                                    1
#define WALKING_RIGHT                                   2
#define WALKING_UP                                      3
#define WALKING_DOWN                                    4
#define DYING                                           5
#define ERASED                                          6 

/*Events*/                                  
#define UP                                              0 
#define LEFT                                            1 
#define RIGHT                                           2 
#define DOWN                                            3 
#define DEAD                                            4
#define PLAYER_GAMEOVER                                 5
#define FINISHSTAGE                                     6

#define LEFTPACE                                        0
#define RIGHTPACE                                       1

#define MAXIMUMSPEED                                    24 
#define DEATHCOUNTER                                    MAXIMUMSPEED
#define DEATHSTEP                                       (DEATHCOUNTER/3)

#define NBLOCKEDUP       (!this->context_->movableObj_->component->blockUp) && (this->GetState() != DYING)
#define NBLOCKEDDOWN     (!this->context_->movableObj_->component->blockDown) && (this->GetState() != DYING)
#define NBLOCKEDLEFT     (!this->context_->movableObj_->component->blockLeft) && (this->GetState() != DYING)
#define NBLOCKEDRIGHT    (!this->context_->movableObj_->component->blockRight) && (this->GetState() != DYING)


class MovementContext;
class Movable;

class Movable{
    private:
        
        int fStSx;
        int fStSy;
        int fLpSx;
        int fLpSy;
        int fRpSx;
        int fRpSy;
        int bStSx;
        int bStSy;
        int bRpSx;
        int bRpSy;
        int bLpSx;
        int bLpSy;
        int lStSx;
        int lStSy;
        int lRpSx;
        int lRpSy;
        int lLpSx;
        int lLpSy;
        int rStSx;
        int rStSy;
        int rRpSx;
        int rRpSy;
        int rLpSx;
        int rLpSy;
        int dS1Sx;
        int dS1Sy;
        int dS2Sx;
        int dS2Sy;
        int dS3Sx;
        int dS3Sy;

    public:
        Component * component;
        Movable(Component * component);
        virtual void SetMovements();
        void WalkUp(int pace);
        void WalkDown(int pace);
        void WalkLeft(int pace);
        void WalkRight(int pace);
        void Turn(int direction);
        void Dies(int step);
};

class MovementState {
  
 protected:
  MovementContext *context_;

 public:
  virtual ~MovementState() {
  }

  void set_context(MovementContext *context);
  int  GetState();  
  int  SetState(int state);  
  int  GetSpeed();
  int  SetSpeed(int speed);
  int  GetDirection();  
  void SetDirection(int direction);
  int  GetSpeedFactor();
  int  TurnPace();
  virtual void Handle(int event) = 0;

};

class MovementContext {

 private:
  MovementState *state_;  
 public:
  Movable *movableObj_;
  int state = IDDLE;
  int speed = 1;
  int direction = DOWN;
  int movementCounter = 0;
  int pace = RIGHTPACE;

  MovementContext(MovementState *state, Movable *movableObj, int speed, int direction );
  void Request(int event);
  ~MovementContext();

  void TransitionTo(MovementState *state);

};


class TurnState : public MovementState {
 
    public:    
        void Handle(int event) override;
  
};

class WalkUp : public MovementState {
    public:
        void Handle(int event) override;
};

class WalkDown : public MovementState {
    public:
        void Handle(int event) override;
};

class WalkLeft : public MovementState {
    public:
        void Handle(int event) override;
};

class WalkRight : public MovementState {
    public:
        void Handle(int event) override;
};

class Die : public MovementState {
    public:
        void Handle(int event) override;
};


#endif