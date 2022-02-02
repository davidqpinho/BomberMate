#include "GameOver.h"

GameOver::GameOver(){
    
    this->bitmap = al_load_bitmap(GameOverImg);
    btnController = new ButtomController();
    
    if(!this->bitmap) 
    {
       printf("Error loading Game Over Bitmap.");
       exit(1);
    }    
    
    this->fontGameOver = al_load_ttf_font(Font_04B_30, 20, 0);
    
    if(!this->fontGameOver)
    {
       printf("Error loading font.");
       exit(1);
    }
  }

GameOver::~GameOver(){
  al_destroy_bitmap(this->bitmap); 
  al_destroy_font(this->fontGameOver); 
  delete btnController;  
}

int GameOver::Handle() {
    this->isLeaving = true;
    return true;
}

void GameOver::Run() {

    al_draw_bitmap(this->bitmap, 0, 0, 0);    
    
    if(this->IsEnabled() && this->isLeaving == false ){
       al_draw_text(this->fontGameOver, al_map_rgb(156,156,156), 160, 350, 0,  ENABLEDTXT);
    }
}

int GameOver::ProcessEvent(ALLEGRO_EVENT ** event) {

    this->EnableTimer = this->EnableTimer >= TICKSTOENABLE ? this->EnableTimer : this->EnableTimer + 1;

    if (this->IsEnabled() && btnController->PressButtom(ALLEGRO_KEY_SPACE)){
      return this->Handle();
    }			

    if(isLeaving){
      this->IsTimerToLeaveFinished();
    }

    return true;
}

bool GameOver::IsEnabled(){

  if(this->EnableTimer >= TICKSTOENABLE){    
    return true;
  }

  return false;
}

void GameOver::IsTimerToLeaveFinished(){
  if(this->TimerToLeave >= TICKSTOENABLE){
    this->scene_->TransitionTo(new Menu());    
  }

  this->TimerToLeave++;
}