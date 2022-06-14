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
#define ROCKWALL_D3_SX   702     //D3
#define ROCKWALL_D3_SY   469     //D3
#define ROCKWALL_D2_SX   1244    //D2
#define ROCKWALL_D2_SY   373     //D2
#define ROCKWALL_D1_SX   1135    //D1
#define ROCKWALL_D1_SY   373     //D1
#define ROCKWALL_SX      1027  
#define ROCKWALL_SY      373   
#define ROCKWALL_SH      86
#define ROCKWALL_SW      100
#define BCKW_D1_SX       1030
#define BCKW_D1_SY       180
#define BCKW_D2_SX       1135
#define BCKW_D2_SY       180
#define BCKW_D3_SX       1245
#define BCKW_D3_SY       180
#define DEST_STEP1       5  
#define DEST_STEP2       10
#define DEST_STEP3       15
#define DEST_END         20

class DestructableWall : public Component, public Wall {   
 private:
  int destructionCounter = 0;
  int WallType;
  float DS1_SX, DS1_SY, DS2_SX, DS2_SY, DS3_SX, DS3_SY;

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