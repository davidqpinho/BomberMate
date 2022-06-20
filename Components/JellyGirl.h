#ifndef __JELLY_GIRL_H_
#define __JELLY_GIRL_H_

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

#define JELLY_GIRL_SH  76
#define JELLY_GIRL_SW  64

#define JELLY_GIRL_F_ST_SX  783
#define JELLY_GIRL_F_ST_SY  584
#define JELLY_GIRL_F_LP_SX  12
#define JELLY_GIRL_F_LP_SY  665
#define JELLY_GIRL_F_RP_SX  710 
#define JELLY_GIRL_F_RP_SY  584
/////////////////////////////////////
#define JELLY_GIRL_B_ST_SX  80 
#define JELLY_GIRL_B_ST_SY  584
#define JELLY_GIRL_B_RP_SX  294
#define JELLY_GIRL_B_RP_SY  584
#define JELLY_GIRL_B_LP_SX  150
#define JELLY_GIRL_B_LP_SY  584
////////////////////////////////////
#define JELLY_GIRL_L_ST_SX  80  
#define JELLY_GIRL_L_ST_SY  664
#define JELLY_GIRL_L_RP_SX  294
#define JELLY_GIRL_L_RP_SY  664
#define JELLY_GIRL_L_LP_SX  150
#define JELLY_GIRL_L_LP_SY  664
///////////////////////////////////
#define JELLY_GIRL_R_ST_SX  360 
#define JELLY_GIRL_R_ST_SY  668
#define JELLY_GIRL_R_RP_SX  572
#define JELLY_GIRL_R_RP_SY  668
#define JELLY_GIRL_R_LP_SX  433
#define JELLY_GIRL_R_LP_SY  668
////////////////////////////////////
#define JELLY_GIRL_D_S1_SX  440
#define JELLY_GIRL_D_S1_SY  584
#define JELLY_GIRL_D_S2_SX  508
#define JELLY_GIRL_D_S2_SY  584
#define JELLY_GIRL_D_S3_SX  572
#define JELLY_GIRL_D_S3_SY  584

using namespace std;
class JellyGirlVisitor;

class JellyGirl : public Component, public Movable, public Mob {
 private:
  int GetEvent(int direction);
  int tempCounter = 0;
 public:  
  int playerColumn=-1, playerRow=-1;
  MovementContext *movementStateMachine;  
  JellyGirlVisitor * visitor;
  JellyGirl(int row, int column) ; 
  ~JellyGirl();

  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  
};

class JellyGirlVisitor : public Visitor {
 private:
  JellyGirl * jellyGirl;
 public:  
  JellyGirlVisitor(JellyGirl * jellyGirl);
  void VisitPlayerOne(const PlayerOne *player) const override;
  void VisitConsumableItem(const ConsumableItem * element) const override {};
  void VisitBomb(const Bomb * element) const override;
  void VisitWall(const Wall *element) const override;
  void VisitMob(const Mob *element) const override;

};

#endif