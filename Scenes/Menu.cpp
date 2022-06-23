#include "Menu.h"

  Menu::Menu(){
    
    this->bitmap = al_load_bitmap(MenuImg);
    btnController = new ButtomController();
    
    if(!this->bitmap) 
    {
       printf("Error loading Menu Bitmap.");
       exit(1);
    }

    this->fontMenu = al_load_ttf_font(Font_04B_30, 36, 0);
    
    if(!this->fontMenu)
    {
       printf("Error loading font.");
       exit(1);
    }
 
  }

  Menu::~Menu(){
    al_destroy_bitmap(this->bitmap);
    al_destroy_font(this->fontMenu);   
    delete btnController;  
  }
  
  void Menu::Run() {   
      
      al_draw_bitmap(this->bitmap, 0, 0, 0);
      
      switch (this->mainMenuStatus)
      {
        case NEWGAME:
          al_draw_text(this->fontMenu, OPT_ON, NGX, NGY, 0,  NEWGAME_TXT);
          al_draw_text(this->fontMenu, OPT_OFF, LGX, LGY, 0, LOADGAME_TXT);
          al_draw_text(this->fontMenu, OPT_OFF, EXX, EXY, 0, EXITGAME_TXT); 
          break;
        case LOADGAME:
          al_draw_text(this->fontMenu, OPT_OFF, NGX, NGY, 0, NEWGAME_TXT);
          al_draw_text(this->fontMenu, OPT_ON, LGX, LGY, 0,  LOADGAME_TXT);
          al_draw_text(this->fontMenu, OPT_OFF, EXX, EXY, 0, EXITGAME_TXT);
          break;
        case EXITGAME:
          al_draw_text(this->fontMenu, OPT_OFF, NGX, NGY, 0, NEWGAME_TXT);
          al_draw_text(this->fontMenu, OPT_OFF, LGX, LGY, 0, LOADGAME_TXT);
          al_draw_text(this->fontMenu, OPT_ON, EXX, EXY, 0,  EXITGAME_TXT); 
          break;
        default:
          break;
      }  

  }

  int Menu::Handle(){
    switch (this->mainMenuStatus)
    {
      case NEWGAME:
        this->scene_->TransitionTo(new Stage(FIELDSTAGE, 0, 1, 8, 1));        
        break;
      case LOADGAME:
        if(CheckIfFileExists()){        
          this->scene_->TransitionTo(new StageTransition(
            ReadIntFromTag("stage"), 
            ReadIntFromTag("life"), 
            ReadIntFromTag("bombStrength"), 
            ReadIntFromTag("speed"), 
            ReadIntFromTag("nOBombs")
          ));
        }else{
          this->scene_->TransitionTo(new Stage(FIELDSTAGE, 0, 1, 8, 1));
        }       
        break;
      case EXITGAME:
        return false;
        break;      
      default:
        break;
    }
    return true;
  }

  int Menu::ProcessEvent(ALLEGRO_EVENT ** event) {    
    
		if (btnController->PressButtom(ALLEGRO_KEY_UP))
    {
      this->mainMenuStatus = this->mainMenuStatus > NEWGAME ? this->mainMenuStatus - 1: this->mainMenuStatus;
    }
			
		if (btnController->PressButtom(ALLEGRO_KEY_DOWN)){
      this->mainMenuStatus = this->mainMenuStatus < EXITGAME ? this->mainMenuStatus + 1: this->mainMenuStatus;
    }		

    if (btnController->PressButtom(ALLEGRO_KEY_SPACE)){
      return this->Handle();
    }			

    return true;
  }