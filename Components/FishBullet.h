#ifndef __FISH_BULLET_H_
#define __FISH_BULLET_H_

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

#define FISH_BULLET_SH  76
#define FISH_BULLET_SW  64 //89

#define FISH_BULLET_F_ST_SX  445
#define FISH_BULLET_F_ST_SY  0
#define FISH_BULLET_F_LP_SX  510
#define FISH_BULLET_F_LP_SY  0
#define FISH_BULLET_F_RP_SX  445
#define FISH_BULLET_F_RP_SY  0
#define FISH_BULLET_B_ST_SX  295
#define FISH_BULLET_B_ST_SY  0
#define FISH_BULLET_B_RP_SX  380
#define FISH_BULLET_B_RP_SY  0
#define FISH_BULLET_B_LP_SX  295
#define FISH_BULLET_B_LP_SY  0
#define FISH_BULLET_L_ST_SX  25
#define FISH_BULLET_L_ST_SY  0
#define FISH_BULLET_L_RP_SX  94
#define FISH_BULLET_L_RP_SY  0
#define FISH_BULLET_L_Lp_SX  25
#define FISH_BULLET_L_LP_SY  0
#define FISH_BULLET_R_ST_SX  154
#define FISH_BULLET_R_ST_SY  0
#define FISH_BULLET_R_RP_SX  225
#define FISH_BULLET_R_RP_SY  0
#define FISH_BULLET_R_LP_SX  154
#define FISH_BULLET_R_LP_SY  0
#define FISH_BULLET_D_S1_SX  25
#define FISH_BULLET_D_S1_SY  0
#define FISH_BULLET_D_S2_SX  25
#define FISH_BULLET_D_S2_SY  0
#define FISH_BULLET_D_S3_SX  25
#define FISH_BULLET_D_S3_SY  0

using namespace std;
class FishBulletVisitor;

class FishBullet : public Component, public Movable, public Mob {
 private:
  int direction;
  int GetEvent(int direction);
  int tempCounter = 0;
 public:  
  MovementContext *movementStateMachine;
  
  FishBulletVisitor * visitor;
  FishBullet(int row, int column, int direction) ; 
  ~FishBullet();

  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  
};

class FishBulletVisitor : public Visitor {
 private:
  FishBullet * fishBullet;
 public:  
  FishBulletVisitor(FishBullet * fishBullet);
  void VisitPlayerOne(const PlayerOne *player) const override {};
  void VisitConsumableItem(const ConsumableItem * element) const override {};
  void VisitBomb(const Bomb * element) const override;
  void VisitWall(const Wall *element) const override;
  void VisitMob(const Mob *element) const override;

};

#endif