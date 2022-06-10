#ifndef __SHOTTER_PENGUIN_H_
#define __SHOTTER_PENGUIN_H_

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

#define SHOTTER_PENGUIN_SH  66
#define SHOTTER_PENGUIN_SW  64

#define SHOTTER_PENGUIN_F_ST_SX  275//0
#define SHOTTER_PENGUIN_F_ST_SY  175//175
#define SHOTTER_PENGUIN_F_LP_SX  350
#define SHOTTER_PENGUIN_F_LP_SY  175
#define SHOTTER_PENGUIN_F_RP_SX  500
#define SHOTTER_PENGUIN_F_RP_SY  175
/////////////////////////////////////
#define SHOTTER_PENGUIN_B_ST_SX  0
#define SHOTTER_PENGUIN_B_ST_SY  175
#define SHOTTER_PENGUIN_B_RP_SX  70
#define SHOTTER_PENGUIN_B_RP_SY  175
#define SHOTTER_PENGUIN_B_LP_SX  215
#define SHOTTER_PENGUIN_B_LP_SY  175
////////////////////////////////////
#define SHOTTER_PENGUIN_L_ST_SX  0
#define SHOTTER_PENGUIN_L_ST_SY  237
#define SHOTTER_PENGUIN_L_RP_SX  70
#define SHOTTER_PENGUIN_L_RP_SY  237
#define SHOTTER_PENGUIN_L_LP_SX  630
#define SHOTTER_PENGUIN_L_LP_SY  175
///////////////////////////////////
#define SHOTTER_PENGUIN_R_RP_SX  350 
#define SHOTTER_PENGUIN_R_RP_SY  237
#define SHOTTER_PENGUIN_R_LP_SX  215
#define SHOTTER_PENGUIN_R_LP_SY  237
#define SHOTTER_PENGUIN_R_ST_SX  140
#define SHOTTER_PENGUIN_R_ST_SY  237
////////////////////////////////////
#define SHOTTER_PENGUIN_D_S1_SX  495
#define SHOTTER_PENGUIN_D_S1_SY  735
#define SHOTTER_PENGUIN_D_S2_SX  560
#define SHOTTER_PENGUIN_D_S2_SY  735
#define SHOTTER_PENGUIN_D_S3_SX  630
#define SHOTTER_PENGUIN_D_S3_SY  735

using namespace std;
class ShotterPenguinVisitor;

class ShotterPenguin : public Component, public Movable, public Mob {
 private:
  int GetEvent(int direction);
  int tempCounter = 0;
 public:  
  MovementContext *movementStateMachine;
  
  ShotterPenguinVisitor * visitor;
  ShotterPenguin(int row, int column) ; 
  ~ShotterPenguin();

  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  
};

class ShotterPenguinVisitor : public Visitor {
 private:
  ShotterPenguin * shotterPenguin;
 public:  
  ShotterPenguinVisitor(ShotterPenguin * shotterPenguin);
  void VisitPlayerOne(const PlayerOne *player) const override {};
  void VisitConsumableItem(const ConsumableItem * element) const override {};
  void VisitBomb(const Bomb * element) const override;
  void VisitWall(const Wall *element) const override;
  void VisitMob(const Mob *element) const override;

};

#endif