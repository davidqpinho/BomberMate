#ifndef __CAPTAIN_PENGUIN_H_
#define __CAPTAIN_PENGUIN_H_

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

#define CAPTAIN_PENGUIN_SH  66
#define CAPTAIN_PENGUIN_SW  64

#define CAPTAIN_PENGUIN_F_ST_SX  0
#define CAPTAIN_PENGUIN_F_ST_SY  298
#define CAPTAIN_PENGUIN_F_LP_SX  70
#define CAPTAIN_PENGUIN_F_LP_SY  298
#define CAPTAIN_PENGUIN_F_RP_SX  215
#define CAPTAIN_PENGUIN_F_RP_SY  298
/////////////////////////////////////
#define CAPTAIN_PENGUIN_B_ST_SX  420
#define CAPTAIN_PENGUIN_B_ST_SY  237
#define CAPTAIN_PENGUIN_B_RP_SX  630
#define CAPTAIN_PENGUIN_B_RP_SY  237
#define CAPTAIN_PENGUIN_B_LP_SX  485
#define CAPTAIN_PENGUIN_B_LP_SY  237
////////////////////////////////////
#define CAPTAIN_PENGUIN_L_ST_SX  275
#define CAPTAIN_PENGUIN_L_ST_SY  298
#define CAPTAIN_PENGUIN_L_RP_SX  350
#define CAPTAIN_PENGUIN_L_RP_SY  298
#define CAPTAIN_PENGUIN_L_LP_SX  500
#define CAPTAIN_PENGUIN_L_LP_SY  298
///////////////////////////////////
#define CAPTAIN_PENGUIN_R_RP_SX  65
#define CAPTAIN_PENGUIN_R_RP_SY  360
#define CAPTAIN_PENGUIN_R_LP_SX  630
#define CAPTAIN_PENGUIN_R_LP_SY  298
#define CAPTAIN_PENGUIN_R_ST_SX  560
#define CAPTAIN_PENGUIN_R_ST_SY  298
////////////////////////////////////
#define CAPTAIN_PENGUIN_D_S1_SX  495
#define CAPTAIN_PENGUIN_D_S1_SY  735
#define CAPTAIN_PENGUIN_D_S2_SX  560
#define CAPTAIN_PENGUIN_D_S2_SY  735
#define CAPTAIN_PENGUIN_D_S3_SX  630
#define CAPTAIN_PENGUIN_D_S3_SY  735

using namespace std;
class CaptainPenguinVisitor;

class CaptainPenguin : public Component, public Movable, public Mob {
 private:
  int GetEvent(int direction);
  int tempCounter = 0;
 public:  
  MovementContext *movementStateMachine;
  
  CaptainPenguinVisitor * visitor;
  CaptainPenguin(int row, int column) ; 
  ~CaptainPenguin();

  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  
};

class CaptainPenguinVisitor : public Visitor {
 private:
  CaptainPenguin * captainPenguin;
 public:  
  CaptainPenguinVisitor(CaptainPenguin * captainPenguin);
  void VisitPlayerOne(const PlayerOne *player) const override {};
  void VisitConsumableItem(const ConsumableItem * element) const override {};
  void VisitBomb(const Bomb * element) const override;
  void VisitWall(const Wall *element) const override;
  void VisitMob(const Mob *element) const override;

};

#endif