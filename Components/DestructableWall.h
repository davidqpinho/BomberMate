#ifndef __DESTRUCTABLE_WALL_H_
#define __DESTRUCTABLE_WALL_H_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../Assets/assets.h"
#include "../Engine/Component.h"
#include "../Scenes/Stage.h"
#include "../Engine/BaseClass.h"

#define BRICKWALL_SX  920
#define BRICKWALL_SY  180
#define BRICKWALL_SH  BLOCKHEIGHT
#define BRICKWALL_SW  BLOCKWIDTH
#define BCKW_D1_SX    1030
#define BCKW_D1_SY    180
#define BCKW_D2_SX    1135
#define BCKW_D2_SY    180
#define BCKW_D3_SX    1245
#define BCKW_D3_SY    180
#define DEST_STEP1    5  
#define DEST_STEP2    10
#define DEST_STEP3    15
#define DEST_END      20

class DestructableWall : public Component, public Wall {   
 private:
  int destructionCounter = 0;
  int WallType;

 public:
  
  DestructableWall(int DestructableWall, int row, int column, int consumable); 
  ~DestructableWall();
  
  void SetDestructionState(int step);
  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  
};

#endif