#ifndef __OCTOPUS_H_
#define __OCTOPUS_H_

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

#define OCTOPUS_SH  76
#define OCTOPUS_SW  64

#define OCTOPUS_F_ST_SX  853
#define OCTOPUS_F_ST_SY  425
#define OCTOPUS_F_LP_SX  853
#define OCTOPUS_F_LP_SY  425
#define OCTOPUS_F_RP_SX  853
#define OCTOPUS_F_RP_SY  668
/////////////////////////////////////
#define OCTOPUS_B_ST_SX  642
#define OCTOPUS_B_ST_SY  667
#define OCTOPUS_B_RP_SX  713
#define OCTOPUS_B_RP_SY  667
#define OCTOPUS_B_LP_SX  783
#define OCTOPUS_B_LP_SY  667
////////////////////////////////////
#define OCTOPUS_L_ST_SX  12
#define OCTOPUS_L_ST_SY  750
#define OCTOPUS_L_RP_SX  85
#define OCTOPUS_L_RP_SY  750
#define OCTOPUS_L_LP_SX  225
#define OCTOPUS_L_LP_SY  750
///////////////////////////////////
#define OCTOPUS_R_RP_SX  363 
#define OCTOPUS_R_RP_SY  750
#define OCTOPUS_R_LP_SX  500
#define OCTOPUS_R_LP_SY  750
#define OCTOPUS_R_ST_SX  433
#define OCTOPUS_R_ST_SY  750
////////////////////////////////////
#define OCTOPUS_D_S1_SX  853
#define OCTOPUS_D_S1_SY  190
#define OCTOPUS_D_S2_SX  853
#define OCTOPUS_D_S2_SY  275
#define OCTOPUS_D_S3_SX  853
#define OCTOPUS_D_S3_SY  340

using namespace std;
class OctopusVisitor;

class Octopus : public Component, public Movable, public Mob {
 private:
  int GetEvent(int direction);
  int tempCounter = 0;
 public:  
  MovementContext *movementStateMachine;
  
  OctopusVisitor * visitor;
  Octopus(int row, int column) ; 
  ~Octopus();

  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  
};

class OctopusVisitor : public Visitor {
 private:
  Octopus * octopus;
 public:  
  OctopusVisitor(Octopus * octopus);
  void VisitPlayerOne(const PlayerOne *player) const override {};
  void VisitConsumableItem(const ConsumableItem * element) const override {};
  void VisitBomb(const Bomb * element) const override;
  void VisitWall(const Wall *element) const override;
  void VisitMob(const Mob *element) const override;

};

#endif