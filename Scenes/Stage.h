#ifndef __STAGE_H_
#define __STAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <vector>
#include <list>
#include "../Engine/ScenesRouter.h"
#include "../Assets/assets.h"
#include "../Engine/ButtonController.h"
#include "GameOver.h"
#include "../Engine/Component.h"
#include "../Engine/StageSelector.h"
#include "../Components/StaticComponent.h"
#include "../Engine/EventsObserver.h"
#include "../Engine/MovementState.h"
#include "../Components/Bomb.h"
#include "../Components/ConsumableItem.h"
#include "../Engine/PlayerObserver.h"
#include "../Engine/BombTracker.h"

#define STAGE_RUNNING     0
#define STAGE_GAME_OVER   1
#define STATUS_COLOR      al_map_rgb(255, 171, 0)
#define ST_CL             75
#define ST_R1             50
#define SCORE "SCORE"

#define LIFE_SX           920
#define LIFE_SY           680
#define LIFE_SW           110
#define LIFE_SH           92

#define SPD_SX            1570//
#define SPD_SY            680//
#define SPD_SW            110//
#define SPD_SH            92//

#define STRG_SX           1356
#define STRG_SY           680
#define STRG_SW           106
#define STRG_SH           92

#define NOBS_SX           1139
#define NOBS_SY           680
#define NOBS_SW           106
#define NOBS_SH           92


using namespace std;

  class Stage : public Scene { 
    
  private:
    int stageStatus = STAGE_RUNNING;
    list<Component*> componentList;    
    ALLEGRO_BITMAP * stageMap = NULL;  
    ALLEGRO_FONT * stageFont = NULL;  
    Subject *subject = NULL;
    PlayerObserver * observer = NULL;
    
    int testeCounter = 150;
    void PrintStatus(float x, float y, int value);
    void ProcessVisitors();
    void ProcessMovements();
    void DrawComponentList();
    
  
  public:  

    static ALLEGRO_BITMAP * sheet1;
    static ALLEGRO_BITMAP * sheet2;
    static PlayerSubject * playerSubject;
    static BombSubject * bombSubject;
    static Observer *eventsObserver;
    static vector<Visitor *> visitorlist; 

    Stage(int stage);
    ~Stage();

    int  Handle() override;
    void Run() override;  
    int  ProcessEvent(ALLEGRO_EVENT ** event) override; 
    bool CheckStaticSpots(int Column, int Row); 
    static void GetSheet(Component * component, int sheet);
    void DrawTestRectangle(float dy,float dx,float sh,float sw);
  };  

#endif