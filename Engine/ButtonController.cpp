#include "ButtonController.h"


int ButtomController::PressButtom(int buttom){
    
    list<PressedButtom>::iterator it;
    ALLEGRO_KEYBOARD_STATE keyState;
    int isPressed;

    al_get_keyboard_state(&keyState);
    isPressed = al_key_down(&keyState, buttom);
    
    for (it = this->PressedButtoms.begin(); it != this->PressedButtoms.end(); ++it){
        
        if(it->value == buttom){            
           return EvaluateButtomFromList(&it, isPressed);
        }

    }
    
    if(isPressed){
        AddButtomToList(buttom);        
        return true;
    }
    
    return false;
    
}

void ButtomController::AddButtomToList(int buttom){
    PressedButtom pressedButtom = {.value = buttom, .tick = 0};
    this->PressedButtoms.push_back(pressedButtom);
}

int ButtomController::EvaluateButtomFromList( list<PressedButtom>::iterator * buttom, int isPressed){
    
    
    if(isPressed){                
        
        (*buttom)->tick ++;
        
        if((*buttom)->tick >= TICKSTOPRESS){
            (*buttom)->tick = 0;
            return true;
        }

    }else{
        
        this->PressedButtoms.erase(* buttom);        

    }
    
    return false;

}

ButtomController::ButtomController(){

}


