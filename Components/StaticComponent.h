#ifndef __STATIC_COMPONENT_H_
#define __STATIC_COMPONENT_H_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../Assets/assets.h"
#include "../Engine/Component.h"
#include "../Scenes/Stage.h"

#define BRICK_SX  702
#define BRICK_SY  180
#define BRICK_SH  BLOCKHEIGHT
#define BRICK_SW  BLOCKWIDTH

class StaticComponent : public Component, public Wall {   

 public:
  
  StaticComponent(int StaticComponent, int row, int column); 
  ~StaticComponent();

  void Colide() override;
  void Move() override;
  void Draw() override;
  
  void Accept(Visitor *visitor) const override;
  
};

#endif