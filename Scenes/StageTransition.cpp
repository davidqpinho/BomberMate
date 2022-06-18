#include "StageTransition.h"

StageTransition::StageTransition(
    int stage,
    int life,
    int bombStrength,
    int speed,
    int nOBombs
){
    this->stage = stage;
    this->life = life;
    this->bombStrength = bombStrength;
    this->speed = speed;
    this->nOBombs = nOBombs;
}

StageTransition::~StageTransition(){
}

int StageTransition::Handle() {
    this->scene_->TransitionTo(new Stage(
        this->stage,
        this->life,
        this->bombStrength,
        this->speed,
        this->nOBombs
        )); 
}

void StageTransition::Run() {

}

int StageTransition::ProcessEvent(ALLEGRO_EVENT ** event) {
    this->Handle();
    return true;
}