#ifndef __CONSUMABLE_ITEM_H_
#define __CONSUMABLE_ITEM_H_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../Assets/assets.h"
#include "../Engine/Component.h"
#include "../Scenes/Stage.h"
#include "../Engine/BaseClass.h"
#include "../Components/PlayerOne.h"

#define LIFE    1
#define SPD     2
#define STRG    3
#define NOBS    4

class ConsumableItemVisitor;

class ConsumableItem : public Component {   
 private:
  ConsumableItemVisitor * visitor;
 public:
  
  int ItemType;
  ConsumableItem(int ConsumableItem, int row, int column); 
  ~ConsumableItem();
  
  void SetDestructionState(int step);
  void Colide() override;
  void Move() override;
  void Draw() override;
  void Accept(Visitor *visitor) const override;
  
};

class ConsumableItemVisitor : public Visitor {
 private:
  
  ConsumableItem * consumableItem;  

 public:  
  ConsumableItemVisitor(ConsumableItem * consumableItem);
  void VisitPlayerOne(const PlayerOne *player) const override;
  void VisitConsumableItem(const ConsumableItem * element) const override {};
  void VisitBomb(const Bomb * element) const override {};
  void VisitWall(const Wall *element) const override {};
  void VisitMob(const Mob *element) const override {};
};

#endif