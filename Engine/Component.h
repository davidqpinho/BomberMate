#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <list>
#include "../Assets/assets.h"
#include "Collider.h"

#define   BLOCKHEIGHT     88
#define   BLOCKWIDTH      100

class Component: public VisitorComponent {
  
 public:
  ALLEGRO_BITMAP ** sheet = NULL;
  bool blockUp=false, blockDown=false, blockLeft=false, blockRight=false;
  int zpos = 1, consumable = -1;

  int fStSx_, fStSy_, fLpSx_, fLpSy_, fRpSx_, fRpSy_, 
      bStSx_, bStSy_, bRpSx_, bRpSy_, bLpSx_, bLpSy_, 
      lStSx_, lStSy_, lRpSx_, lRpSy_, lLpSx_, lLpSy_, 
      rStSx_, rStSy_, rRpSx_, rRpSy_, rLpSx_, rLpSy_,
      dS1Sx_, dS1Sy_, dS2Sx_, dS2Sy_, dS3Sx_,dS3Sy_; 

  float sx = -1;  // source x
  float sy = -1;  // source y
  float sw = -1;  // source width (width of region to blit)
  float sh = -1;  // source height (height of region to blit)
  float dx = -1;  // destination x
  float dy = -1;  // destination y
  int row = -1;
  int column = -1;
  bool removed = false;

  void DefineBlockPosition(int row, int column);  
  virtual ~Component() {}
  virtual void Colide() = 0;
  virtual void Move() = 0;
  virtual void Draw() = 0;
  bool BlockRow(int visitorRow, int visitorColumn);
  bool BlockColumn(int visitorColumn, int visitorRow);
  void SetRow(int row);
  void SetColumn(int column);
  float GetX(int column);
  float GetY(int row);
  
};

#endif