#include "StageTransition.h"

StageTransition::StageTransition(int stage){
    this->stage = stage;
}

StageTransition::~StageTransition(){
}

int StageTransition::Handle() {
    this->scene_->TransitionTo(new Stage(this->stage)); 
}

void StageTransition::Run() {

}

int StageTransition::ProcessEvent(ALLEGRO_EVENT ** event) {
    this->Handle();
    return true;
}