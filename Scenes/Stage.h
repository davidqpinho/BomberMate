#ifndef __STAGE_H_
#define __STAGE_H_

#include <stdio.h>
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

#define STAGE_RUNNING     0
#define STAGE_GAME_OVER   1


using namespace std;

  class Stage : public Scene { 
    
  private:
    int stageStatus = STAGE_RUNNING;
    list<Component*> componentList;    
    ALLEGRO_BITMAP * stageMap = NULL;  
    ALLEGRO_FONT * stageFont = NULL;  
    Subject *subject = NULL;
    int testeCounter = 150;
    
    void ProcessVisitors();
    void ProcessMovements();
    void DrawComponentList();
    
  
  public:  

    static ALLEGRO_BITMAP * sheet1;
    static ALLEGRO_BITMAP * sheet2;
    static Observer *eventsObserver;
    static vector<Visitor *> visitorlist; 

    Stage(int stage);
    ~Stage();

    int  Handle() override;
    void Run() override;  
    int  ProcessEvent(ALLEGRO_EVENT ** event) override; 
    bool CheckStaticSpots(int Column, int Row); 
    static void GetSheet(Component * component, int sheet);

  };

  

#endif