#include "Stage.h"

ALLEGRO_BITMAP * Stage::sheet1;
ALLEGRO_BITMAP * Stage::sheet2;
Observer * Stage::eventsObserver;
PlayerSubject * Stage::playerSubject;
BombSubject * Stage::bombSubject;
vector<Visitor *> Stage::visitorlist; 

  Stage::Stage(int stage){
    
    Stage::sheet1 = NULL;
    Stage::sheet2 = NULL;
    Stage::eventsObserver = NULL;
    Stage::playerSubject = new PlayerSubject;
    Stage::bombSubject = new BombSubject;

    Stage::visitorlist = vector<Visitor *>();
    
    subject = new Subject;
    Stage::eventsObserver = new Observer(*subject);
    
    StageSelector * selector = StageSelector::StageFactory(stage);
    this->observer = new PlayerObserver(* Stage::playerSubject);   
    
    if(!Stage::sheet1){
    
      Stage::sheet1 = al_load_bitmap(Sheet1);
      
      if(!Stage::sheet1){
         printf("Error loading Sheet1.");
         exit(1);
      }
    
    }
    
    if(!Stage::sheet2){
    
      Stage::sheet2 = al_load_bitmap(Sheet2);
      
      if(!Stage::sheet2){
         printf("Error loading Sheet2.");
         exit(1);
      }
    
    } 


    selector->GetStageBitmap(&this->stageMap);
    if(!this->stageMap) 
    {
       printf("Error loading Stage Bitmap.");
       exit(1);
    }

    this->stageFont = al_load_ttf_font(Font_04B_30, 36, 0);
    
    if(!this->stageFont)
    {
       printf("Error loading font.");
       exit(1);
    }

    selector->LoadStaticComponents(this->componentList);    
    selector->LoadMobs(this->componentList);
    //selector->LoadDestructableComponents(this->componentList);
    selector->LoadPlayerOne(this->componentList);    
    
    delete selector;
  }

  void Stage::GetSheet(Component * component, int sheet){
    if(sheet == 1){
       component->sheet = &Stage::sheet1;
    }
    if(sheet == 2){
       component->sheet = &Stage::sheet2;
    }
  }

  Stage::~Stage(){

    al_destroy_bitmap(this->stageMap);
    al_destroy_bitmap(Stage::sheet1);
    al_destroy_bitmap(Stage::sheet2);    
    al_destroy_font(this->stageFont);  
    while(!componentList.empty()) delete componentList.front(), componentList.pop_front(); 
    
    for (auto p : Stage::visitorlist){ 
      delete p;
    } Stage::visitorlist.clear();    
    
    subject->Detach(Stage::eventsObserver); 
    delete Stage::eventsObserver;
    delete playerSubject;
    delete bombSubject;
  }
  
  void Stage::Run() {   
     
     al_clear_to_color(al_map_rgb(2, 116, 222));
     al_draw_bitmap(this->stageMap, HEADERSIZE, 0, 0);
     this->DrawComponentList();

     /*Player status*/ 
     al_draw_bitmap_region(this->sheet1, LIFE_SX, LIFE_SY, LIFE_SW, LIFE_SH, 0, 0, 0);//life 88
     al_draw_bitmap_region(this->sheet1, SPD_SX, SPD_SY, SPD_SW, SPD_SH, 2, 92, 0);
     al_draw_bitmap_region(this->sheet1, STRG_SX, STRG_SY, STRG_SW, STRG_SH, 0, 184, 0);
     al_draw_bitmap_region(this->sheet1, NOBS_SX, NOBS_SY, NOBS_SW, NOBS_SH, 2, 276, 0);
     
     this->PrintStatus(ST_CL, ST_R1, this->observer->GetLife());
     this->PrintStatus(ST_CL, ST_R1 + 92, this->observer->GetSpeed());
     this->PrintStatus(ST_CL, ST_R1 + 184, this->observer->GetBombStrength());
     this->PrintStatus(ST_CL, ST_R1 + 276, this->observer->GetNOBombs());

  }

  void Stage::PrintStatus(float x, float y, int value){
    
    char buffer [33];
    
    itoa (value,buffer);
    al_draw_text(this->stageFont, STATUS_COLOR, x, y, 0,  buffer);
  }

  int Stage::Handle(){
    switch (this->stageStatus)
    {
      case STAGE_GAME_OVER:
        this->scene_->TransitionTo(new GameOver());
        break;      
      default:
        break;
    }
    return true;
  }

  void Stage::ProcessVisitors(){

    vector<Visitor *>::iterator visIt;
    list<Component *>::iterator compLsIt;

    for(compLsIt = this->componentList.begin(); compLsIt != this->componentList.end(); ++compLsIt){
        (*compLsIt)->blockDown  = false;
        (*compLsIt)->blockUp    = false;
        (*compLsIt)->blockLeft  = false;
        (*compLsIt)->blockRight = false;

    }

    for(visIt = Stage::visitorlist.begin(); visIt != Stage::visitorlist.end(); ++visIt){
      for(const Component *comp : this->componentList){
        comp->Accept((*visIt));
      }
    }

  }
  
  void Stage::ProcessMovements(){
    
    list<Component*>::iterator it;
    it = this->componentList.begin();
    
    while (it != this->componentList.end())
    {
      if((*it)->removed){
          if((*it)->consumable > -1){
            this->componentList.push_back(new ConsumableItem(
              (*it)->consumable, 
              (*it)->row,
              (*it)->column
              ));
          }

          it = this->componentList.erase(it);
        }else{
          (*it)->Move();
          ++it;
        }
    }
    

  }

  int Stage::ProcessEvent(ALLEGRO_EVENT ** event) {

    
    ALLEGRO_KEYBOARD_STATE keyState;

    if(Stage::eventsObserver->ReadEvent() == PLAYER_GAMEOVER){
      this->stageStatus = STAGE_GAME_OVER;
      this->Handle();
    }

    al_get_keyboard_state(&keyState);

    if (al_key_down(&keyState, ALLEGRO_KEY_SPACE)){
        
      
      if(this->bombSubject->CanSpawnBombs(this->observer->GetNOBombs()) == 1){
        Component * bomb = new Bomb(
          this->observer->GetLine(),
          this->observer->GetColumn(),
          this->observer->GetBombStrength()
        );
        this->componentList.push_back(bomb);
      }
    }

    if(al_key_down(&keyState, ALLEGRO_KEY_UP)){
      
      this->subject->CreateEvent(UP);
    }	

    if(al_key_down(&keyState, ALLEGRO_KEY_DOWN)){
      this->subject->CreateEvent(DOWN);
    }	

    if(al_key_down(&keyState, ALLEGRO_KEY_LEFT)){
      this->subject->CreateEvent(LEFT);
    }		

    if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT)){
      this->subject->CreateEvent(RIGHT);
    }		
    
    this->ProcessMovements();
    this->ProcessVisitors();
    this->bombSubject->UpdateTimer();
    
    return true;
  }

  void Stage::DrawComponentList(){

    list<Component*>::iterator it;
    this->componentList.sort([](const Component * f, const Component * s) { return f->zpos < s->zpos; });
    
        for (it = this->componentList.begin(); it != this->componentList.end(); ++it){
          (*it)->Draw();
          //this->DrawTestRectangle((*it)->dy, (*it)->dx, (*it)->sh, (*it)->sw);
        }
      
  } 

  void Stage::DrawTestRectangle(float dy,float dx,float sh,float sw){
    float by = dy;
    float ey = dy + sh;
    float bx = dx;
    float ex = dx + sw;
    for(float i=0;i<=5; i+=0.1){
      al_draw_pixel(bx, by+i, al_map_rgb(255, 0, 0));
      al_draw_pixel(bx+i, by, al_map_rgb(255, 0, 0));
      al_draw_pixel(ex-i, by, al_map_rgb(255, 0, 0));
      al_draw_pixel(ex, by+i, al_map_rgb(255, 0, 0));
      al_draw_pixel(bx+i, ey, al_map_rgb(255, 0, 0));
      al_draw_pixel(bx, ey-i, al_map_rgb(255, 0, 0));
      al_draw_pixel(ex, ey-i, al_map_rgb(255, 0, 0));
      al_draw_pixel(ex-i, ey, al_map_rgb(255, 0, 0));
    }
  }
  