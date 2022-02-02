#ifndef __GUARD_DOG_H_
#define __GUARD_DOG_H_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "../Assets/assets.h"
#include "../Engine/Component.h"
#include "../Scenes/Stage.h"
#include "../Engine/MovementState.h"
#include "../Engine/BaseClass.h"
#include "../Engine/Collider.h"
#include "../Utils/Utils.h"

#define GUARD_DOG_SH  76
#define GUARD_DOG_SW  64

#define GUARD_DOG_F_ST_SX  80
#define GUARD_DOG_F_ST_SY  504
#define GUARD_DOG_F_LP_SX  150
#define GUARD_DOG_F_LP_SY  504
#define GUARD_DOG_F_RP_SX  294 
#define GUARD_DOG_F_RP_SY  504
#define GUARD_DOG_B_ST_SX  360 
#define GUARD_DOG_B_ST_SY  425
#define GUARD_DOG_B_RP_SX  572
#define GUARD_DOG_B_RP_SY  425
#define GUARD_DOG_B_LP_SX  433
#define GUARD_DOG_B_LP_SY  425
#define GUARD_DOG_L_ST_SX  360 
#define GUARD_DOG_L_ST_SY  504
#define GUARD_DOG_L_RP_SX  572
#define GUARD_DOG_L_RP_SY  504
#define GUARD_DOG_L_Lp_SX  433
#define GUARD_DOG_L_LP_SY  504
#define GUARD_DOG_R_ST_SX  642
#define GUARD_DOG_R_ST_SY  504
#define GUARD_DOG_R_RP_SX  12
#define GUARD_DOG_R_RP_SY  584
#define GUARD_DOG_R_LP_SX  710
#define GUARD_DOG_R_LP_SY  504
#define GUARD_DOG_D_S1_SX  642
#define GUARD_DOG_D_S1_SY  425
#define GUARD_DOG_D_S2_SX  710
#define GUARD_DOG_D_S2_SY  425
#define GUARD_DOG_D_S3_SX  783
#define GUARD_DOG_D_S3_SY  425

using namespace std;
class GuardDogVisitor;

class GuardDog : public Component, public Movable, public Mob {
 private:
  int GetEvent(int direction);
  int tempCounter = 0;
 public:  
  MovementContext *movementStateMachine;
  
  GuardDogVisitor * visitor;
  GuardDog(int row, int column) ; 
  ~GuardDog();

  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  
};

class GuardDogVisitor : public Visitor {
 private:
  GuardDog * guardDog;
 public:  
  GuardDogVisitor(GuardDog * guardDog);
  void VisitPlayerOne(const PlayerOne *player) const override {};
  void VisitBomb(const Bomb * element) const override;
  void VisitWall(const Wall *element) const override;
  void VisitMob(const Mob *element) const override;

};

#endif