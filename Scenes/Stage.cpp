#include "Stage.h"

ALLEGRO_BITMAP * Stage::sheet1;
ALLEGRO_BITMAP * Stage::sheet2;
Observer * Stage::eventsObserver;
vector<Visitor *> Stage::visitorlist; 

  Stage::Stage(int stage){
    
    Stage::sheet1 = NULL;
    Stage::sheet2 = NULL;
    Stage::eventsObserver = NULL;

    Stage::visitorlist = vector<Visitor *>();
    
    subject = new Subject;
    Stage::eventsObserver = new Observer(*subject);
    
    StageSelector * selector = StageSelector::StageFactory(stage);
       
    
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
    selector->LoadDestructableComponents(this->componentList);
    selector->LoadMobs(this->componentList);
    selector->LoadPlayerOne(this->componentList);
    Component * bomb = new Bomb(4,4);
    this->componentList.push_back(bomb);
    
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

  }
  
  void Stage::Run() {   
      
     al_draw_bitmap(this->stageMap, HEADERSIZE, 0, 0);
     this->DrawComponentList();

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
      return this->Handle();
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
    
    this->ProcessVisitors();
    this->ProcessMovements();
   
    return true;
  }

  void Stage::DrawComponentList(){

    list<Component*>::iterator it;
    
        for (it = this->componentList.begin(); it != this->componentList.end(); ++it){
          (*it)->Draw();
        }
      
  } 