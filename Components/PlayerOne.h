#ifndef __PLAYER_ONE_H_
#define __PLAYER_ONE_H_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../Assets/assets.h"
#include "../Engine/Component.h"
#include "../Scenes/Stage.h"
#include "../Engine/MovementState.h"
#include "../Engine/BaseClass.h"
#include "../Engine/Collider.h"
#include "../Engine/PlayerObserver.h"

#define INITIAL_SPEED  8

#define P_ONE_SH  76
#define P_ONE_SW  64
#define P_ONE_F_ST_SX  12
#define P_ONE_F_ST_SY  16
#define P_ONE_F_LP_SX  80
#define P_ONE_F_LP_SY  16
#define P_ONE_F_RP_SX  224 
#define P_ONE_F_RP_SY  16
#define P_ONE_B_ST_SX  294 
#define P_ONE_B_ST_SY  16
#define P_ONE_B_RP_SX  360 
#define P_ONE_B_RP_SY  16
#define P_ONE_B_LP_SX  504 
#define P_ONE_B_LP_SY  16
#define P_ONE_L_ST_SX  572
#define P_ONE_L_ST_SY  16
#define P_ONE_L_RP_SX  644
#define P_ONE_L_RP_SY  16
#define P_ONE_L_Lp_SX  784 
#define P_ONE_L_LP_SY  16
#define P_ONE_R_ST_SX  12
#define P_ONE_R_ST_SY  98
#define P_ONE_R_RP_SX  80
#define P_ONE_R_RP_SY  98
#define P_ONE_R_LP_SX  224 
#define P_ONE_R_LP_SY  98
#define P_ONE_D_S1_SX  294
#define P_ONE_D_S1_SY  98
#define P_ONE_D_S2_SX  360
#define P_ONE_D_S2_SY  98
#define P_ONE_D_S3_SX  430
#define P_ONE_D_S3_SY  98
#define UpdatePlayerStatus  this->observer->SetStatus(this->life, this->bombStrength, this->speed, this->column, this->row, this->nOBombs)


class PlayerOneVisitor;

class PlayerOne : public Component, public Movable {
 
 private:
  int life = 0, bombStrength = 0, speed = 8, nOBombs = 1;
  int initialRow, initialColumn;
  PlayerObserver * observer = NULL;

 public:
  
  MovementContext *movementStateMachine;
  
  PlayerOneVisitor * visitor;
  PlayerOne(int row, int column) ; 
  ~PlayerOne();

  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  
};

class PlayerOneVisitor : public Visitor {
 private:
  PlayerOne * player;
 public:
  PlayerOneVisitor(PlayerOne * player);
  void VisitPlayerOne(const PlayerOne *player) const override {};
  void VisitBomb(const Bomb * element) const override;
  void VisitWall(const Wall *element) const override;
  void VisitMob(const Mob *element) const override;

};

#endif