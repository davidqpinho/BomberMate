#ifndef __BUTTERFLY_H_
#define __BUTTERFLY_H_

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

#define BUTTERFLY_SH  76
#define BUTTERFLY_SW  64

#define BUTTERFLY_F_ST_SX  363
#define BUTTERFLY_F_ST_SY  343
#define BUTTERFLY_F_LP_SX  572
#define BUTTERFLY_F_LP_SY  343
#define BUTTERFLY_F_RP_SX  363 
#define BUTTERFLY_F_RP_SY  343
//////////////////////////////////////////
#define BUTTERFLY_B_ST_SX  642
#define BUTTERFLY_B_ST_SY  263
#define BUTTERFLY_B_RP_SX  710
#define BUTTERFLY_B_RP_SY  260
#define BUTTERFLY_B_LP_SX  642
#define BUTTERFLY_B_LP_SY  263
//////////////////////////////////////////
#define BUTTERFLY_L_ST_SX  642 
#define BUTTERFLY_L_ST_SY  343
#define BUTTERFLY_L_RP_SX  710
#define BUTTERFLY_L_RP_SY  343
#define BUTTERFLY_L_Lp_SX  642
#define BUTTERFLY_L_LP_SY  343
/////////////////////////////////////////
#define BUTTERFLY_R_ST_SX  83
#define BUTTERFLY_R_ST_SY  425
#define BUTTERFLY_R_RP_SX  294
#define BUTTERFLY_R_RP_SY  425
#define BUTTERFLY_R_LP_SX  83
#define BUTTERFLY_R_LP_SY  425
////////////////////////////////////////
#define BUTTERFLY_D_S1_SX  155
#define BUTTERFLY_D_S1_SY  343
#define BUTTERFLY_D_S2_SX  230
#define BUTTERFLY_D_S2_SY  343
#define BUTTERFLY_D_S3_SX  294
#define BUTTERFLY_D_S3_SY  343

using namespace std;
class ButterflyVisitor;

class Butterfly : public Component, public Movable, public Mob {
 private:
  int GetEvent(int direction);
  int tempCounter = 0;
 public:  
  MovementContext *movementStateMachine;
  
  ButterflyVisitor * visitor;
  Butterfly(int row, int column) ; 
  ~Butterfly();

  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  
};

class ButterflyVisitor : public Visitor {
 private:
  Butterfly * butterfly;
 public:  
  ButterflyVisitor(Butterfly * butterfly);
  void VisitPlayerOne(const PlayerOne *player) const override {};
  void VisitConsumableItem(const ConsumableItem * element) const override {};
  void VisitBomb(const Bomb * element) const override;
  void VisitWall(const Wall *element) const override;
  void VisitMob(const Mob *element) const override;

};

#endif