#ifndef __BOMB_H_
#define __BOMB_H_

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../Utils/Utils.h"
#include "../Assets/assets.h"
#include "../Engine/Component.h"
#include "../Scenes/Stage.h"
#include "../Engine/BaseClass.h"
#include "../Engine/Collider.h"
#include "../Engine/BombTracker.h"


#define BOMB_SX             922
#define BOMB_SY             180
#define BOMB_SH             BLOCKHEIGHT
#define BOMB_SW             BLOCKWIDTH
#define BOMBCOUNTERMAX      64
#define BOMBCOUNTERSTEP     8
#define SWSHEET             108.3
#define SHSHEET             95
#define XOFFSET             925
#define YOFFSET             25
#define BURNING             0
#define EXPLODED            1
#define VANISHED            2
#define EXPLOSIONEND        30
#define EXPLOSIONSTEP       3
#define EXPFINALSTEP        12

using namespace std;

class BombVisitor;

class Bomb : public Component{ 

  private:
  struct ExplodedPosition {   
      int row;   
      int column;    
  };   
  BombObserver * bombObserver = NULL;

 public:
  
  int state, bombCounter = 0, strength = 1, bombColumn = 5, explosionCounter = 0;
  int blockUpLv, blockDownLv, blockRightLv, blockLeftLv;
  bool rangeDefined = false;
  Wall * upWall, * bottomWall, * leftWall, * rigthWall;
  BombVisitor * visitor;
  Bomb(int row, int column, int bombStrenght); 
  ~Bomb();

  vector<ExplodedPosition> explodedPlaces;
  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  void DrawExplosion();
  void DrawFinalStep();
  void DrawExplodedPlace(int row, int column, int sx, int sy, int sw, int sh, int fineX, int fineY);
  void DrawExplosionLevel(int Level);
  void DrawExplosionEnd(float sxUp, float syUp, float sxDown, float syDown, float sxLeft, float syLeft, float sxRight, float syRight);
  void DrawNotBlocked(int shrow, int shcolumn, int fineX, int fineY, int row_, int column_, float sx_, float sy_, int blockedLv, int ExplosionLv);
  bool CheckIfHit(float by, float ey, float bx, float ex) const;
  
};

class BombVisitor : public Visitor {
 private:
  
  Bomb * bomb;  

 public:  
  BombVisitor(Bomb * bomb);
  void VisitPlayerOne(const PlayerOne *player) const override {};
  void VisitWall(const Wall *element) const override;
  void VisitMob(const Mob *element) const override {};
  void VisitBomb(const Bomb * element) const override {};
  void VisitConsumableItem(const ConsumableItem * element) const override {};
  void ProcessVisitor(Component * Component) const; 
  bool SetBlockLevel(int bombEqualDirection, int wallEqualDirection, int higherLevel, int lowerLevel, int * level) const;
};

#endif