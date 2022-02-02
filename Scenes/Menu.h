#ifndef __MENU_H_
#define __MENU_H_

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "../Engine/ScenesRouter.h"
#include "../Assets/assets.h"
#include "../Engine/ButtonController.h"
#include "GameOver.h"
#include "Stage.h"

#define  NEWGAME          0
#define  NEWGAME_TXT      "NEW GAME"
#define  NGX              400
#define  NGY              300
#define  LOADGAME         1
#define  LOADGAME_TXT     "LOAD GAME"
#define  LGX              400
#define  LGY              344
#define  EXITGAME         2
#define  EXITGAME_TXT     "EXIT GAME"
#define  EXX              400
#define  EXY              388
#define  OPT_ON           al_map_rgb(173, 35, 17)
#define  OPT_OFF          al_map_rgb(17, 100, 173)

class Menu : public Scene { 

 private:
  int mainMenuStatus = NEWGAME;
  ButtomController * btnController;
  ALLEGRO_BITMAP * bitmap = NULL;
  ALLEGRO_FONT * fontMenu = NULL;    
 
 public:  
  
  Menu();
  ~Menu();

  int Handle() override;

  void Run() override;

  int ProcessEvent(ALLEGRO_EVENT ** event) override;
  

};

#endif