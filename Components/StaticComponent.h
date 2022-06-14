#ifndef __STATIC_COMPONENT_H_
#define __STATIC_COMPONENT_H_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../Assets/assets.h"
#include "../Engine/Component.h"
#include "../Scenes/Stage.h"

#define BRICK_SX    702 //702
#define BRICK_SY    180 //180
#define ROCK_SX     807.5
#define ROCK_SY     469
#define ROCK_SH     86
#define ROCK_SW     100
#define BRICK_SH    BLOCKHEIGHT
#define BRICK_SW    BLOCKWIDTH

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