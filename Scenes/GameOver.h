#ifndef __GAME_OVER_H_
#define __GAME_OVER_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../Engine/ScenesRouter.h"
#include "../Engine/ScenesRouter.h"
#include "../Assets/assets.h"
#include "../Engine/ButtonController.h"
#include "Menu.h"


class GameOver : public Scene {

 #define TIMETOENABLE         1
 #define TICKSTOENABLE  (int)(TIMETOENABLE*FPS)
 #define ENABLEDTXT           "PRESS SPACE TO LEAVE"

 private:
  ButtomController * btnController;
  ALLEGRO_BITMAP * bitmap = NULL;
  ALLEGRO_BITMAP * teste = NULL;
  ALLEGRO_FONT * fontGameOver = NULL;  
  int EnableTimer = 0;
  int TimerToLeave = 0;
  bool isLeaving = false;
  bool IsEnabled();
  void IsTimerToLeaveFinished();
  
 
 public:
  GameOver();
  ~GameOver();
  int Handle() override;
  void Run() override;
  int ProcessEvent(ALLEGRO_EVENT ** event) override;
};

#endif