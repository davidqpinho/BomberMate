#ifndef __BUTTON_CONTROLLER_H_
#define __BUTTON_CONTROLLER_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <list>
#include <algorithm> 
#include "../Main.h"

using namespace std;

#define TIMETOPRESS         0.15
#define TICKSTOPRESS  (int)(TIMETOPRESS*FPS)

class ButtomController {
 
 private:  
 
  struct PressedButtom {   
      int value;   
      int tick;    
  };   

  list<PressedButtom> PressedButtoms;   
 
 public:
  ButtomController();
  int PressButtom(int buttom);
  int FindButtom(int buttom);  
  void AddButtomToList(int buttom);
  int EvaluateButtomFromList( list<PressedButtom>::iterator * buttom, int isPressed);
  
};

#endif