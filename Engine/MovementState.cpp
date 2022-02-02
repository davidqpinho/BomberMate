#include "MovementState.h"

Movable::Movable(Component * component){
    this->component = component;
}

void Movable::WalkUp(int pace){
    if (pace == LEFTPACE)
    {
        this->component->sx = this->bLpSx;
        this->component->sy = this->bLpSy;
    }else{
        this->component->sx = this->bRpSx;
        this->component->sy = this->bRpSy;
    }

}

void Movable::WalkDown(int pace){
    if (pace == LEFTPACE)
    {
        this->component->sx = this->fLpSx;
        this->component->sy = this->fLpSy;
    }else{
        this->component->sx = this->fRpSx;
        this->component->sy = this->fRpSy;
    }

}

void Movable::WalkLeft(int pace){
    if (pace == LEFTPACE)
    {
        this->component->sx = this->lLpSx;
        this->component->sy = this->lLpSy;
    }else{
        this->component->sx = this->lRpSx;
        this->component->sy = this->lRpSy;
    }

}

void Movable::WalkRight(int pace){
    if (pace == LEFTPACE)
    {
        this->component->sx = this->rLpSx;
        this->component->sy = this->rLpSy;
    }else{
        this->component->sx = this->rRpSx;
        this->component->sy = this->rRpSy;
    }

}

void Movable::Turn(int direction){    
    switch (direction)
    {
    case UP:
        this->component->sx = this->bStSx;
        this->component->sy = this->bStSy;
        break;
    case LEFT:
        this->component->sx = this->lStSx;
        this->component->sy = this->lStSy;
        break;
    case RIGHT:
        this->component->sx = this->rStSx;
        this->component->sy = this->rStSy;
        break;    
    default:
        this->component->sx = this->fStSx;
        this->component->sy = this->fStSy;
        break;
    }
}

void Movable::Dies(int step){    
    if(step == 0){
        this->component->sx = this->component->dS1Sx_;
        this->component->sy = this->component->dS1Sy_;
    }else if(step == 1){
        this->component->sx = this->component->dS2Sx_;
        this->component->sy = this->component->dS2Sy_;
    }else{
        this->component->sx = this->component->dS3Sx_;
        this->component->sy = this->component->dS3Sy_;
    }    
    
}

void Movable::SetMovements(){

    this->fStSx = this->component->fStSx_;
    this->fStSy = this->component->fStSy_;
    this->fLpSx = this->component->fLpSx_;
    this->fLpSy = this->component->fLpSy_;
    this->fRpSx = this->component->fRpSx_;
    this->fRpSy = this->component->fRpSy_;
    this->bStSx = this->component->bStSx_;
    this->bStSy = this->component->bStSy_;
    this->bRpSx = this->component->bRpSx_;
    this->bRpSy = this->component->bRpSy_;
    this->bLpSx = this->component->bLpSx_;
    this->bLpSy = this->component->bLpSy_;
    this->lStSx = this->component->lStSx_;
    this->lStSy = this->component->lStSy_;
    this->lRpSx = this->component->lRpSx_;
    this->lRpSy = this->component->lRpSy_;
    this->lLpSx = this->component->lLpSx_;
    this->lLpSy = this->component->lLpSy_;
    this->rStSx = this->component->rStSx_;
    this->rStSy = this->component->rStSy_;
    this->rRpSx = this->component->rRpSx_;
    this->rRpSy = this->component->rRpSy_;
    this->rLpSx = this->component->rLpSx_;
    this->rLpSy = this->component->rLpSy_;
    this->dS1Sx = this->component->dS1Sx_;
    this->dS1Sy = this->component->dS1Sy_;
    this->dS2Sx = this->component->dS2Sx_;
    this->dS2Sy = this->component->dS2Sy_;
    this->dS3Sx = this->component->dS3Sx_;
    this->dS3Sy = this->component->dS3Sy_;

}

void MovementState::set_context(MovementContext *context) {

    this->context_ = context;

}

int MovementState::GetSpeedFactor(){
    return (MAXIMUMSPEED - this->context_->speed);
}

int  MovementState::GetState(){
    return this->context_->state;
}  

int  MovementState::GetSpeed(){
    return this->context_->speed;
}

int  MovementState::GetDirection(){
    return this->context_->direction;
}

void MovementState::SetDirection(int direction){
    this->context_->direction = direction;
}

int  MovementState::SetState(int state){
    this->context_->state = state;
}

int  MovementState::SetSpeed(int speed){
    this->context_->speed = speed;
}

int MovementState::TurnPace(){
    this->context_->pace = this->context_->pace == RIGHTPACE ? LEFTPACE: RIGHTPACE; 
    return this->context_->pace;
}

MovementContext::MovementContext(MovementState *state, Movable *movableObj, int speed, int direction) : state_(nullptr){

    this->speed = speed;
    this->direction = direction;
    this->TransitionTo(state);
    this->movableObj_ = movableObj;

}

MovementContext::~MovementContext() {
    delete state_;
}


void MovementContext::TransitionTo(MovementState *state) {    
    this->state_ = state;
    this->state_->set_context(this);
}

void MovementContext::Request(int event){
    this->state_->Handle(event);
}

void TurnState::Handle(int event){
    if(event == DEAD || event == this->GetDirection()){
        switch (event)
        {
            case UP:
                this->context_->TransitionTo(new WalkUp());
                break;
            case DOWN:
                this->context_->TransitionTo(new WalkDown());
                break;
            case LEFT:
                this->context_->TransitionTo(new WalkLeft());
                break;
            case RIGHT:
                this->context_->TransitionTo(new WalkRight());
                break;  
            case DEAD:
                this->context_->TransitionTo(new Die());
                break;          
            default:
                break;
        }
    }else{                 
       
       if(event != IDDLE){
           this->SetDirection(event);
           this->context_->movableObj_->Turn(event);
       }else{
           this->context_->movableObj_->Turn(this->GetDirection());
       }

    }
}

void WalkUp::Handle(int event){
    
    int speedFactor = this->GetSpeedFactor();
    if(NBLOCKEDUP){
        if(this->GetState() != WALKING_UP){
    
            this->context_->movementCounter = 0;
            this->SetState(WALKING_UP);
            this->SetDirection(UP);
            this->context_->movableObj_->WalkUp(this->TurnPace());
        
        }

        if( speedFactor > this->context_->movementCounter ){
            
            this->context_->movementCounter++;
            this->context_->movableObj_->component->dy-=BLOCKHEIGHT/speedFactor;
            if(this->context_->movementCounter == speedFactor/2)
             this->context_->movableObj_->WalkUp(this->TurnPace());         

        }else{            
            
            this->context_->movableObj_->component->SetRow(this->context_->movableObj_->component->row - 1); 
            this->context_->movementCounter = 0;
            this->SetState(TURN);
            this->context_->TransitionTo(new TurnState());
            
        }
    }else{
        this->SetState(TURN);
                this->context_->TransitionTo(new TurnState());
    } 
    
    
}

void WalkDown::Handle(int event){
    
    int speedFactor = this->GetSpeedFactor();
    if(NBLOCKEDDOWN){
        if(this->GetState() != WALKING_DOWN){
        
            this->context_->movementCounter = 0;
            this->SetState(WALKING_DOWN);
            this->SetDirection(DOWN);
            this->context_->movableObj_->WalkDown(this->TurnPace());
        
        }

        if( speedFactor > this->context_->movementCounter ){
            this->context_->movementCounter++;
            this->context_->movableObj_->component->dy+=BLOCKHEIGHT/speedFactor; 
            if(this->context_->movementCounter == speedFactor/2)
             this->context_->movableObj_->WalkDown(this->TurnPace()); 
        }else{
            
            this->context_->movableObj_->component->SetRow(this->context_->movableObj_->component->row + 1);            
            this->context_->movementCounter = 0;
            this->SetState(TURN);
            this->context_->TransitionTo(new TurnState());
        }
    }else{
        this->SetState(TURN);
                this->context_->TransitionTo(new TurnState());
    } 
}

void WalkLeft::Handle(int event){
    
    int speedFactor = this->GetSpeedFactor();
    
    if(NBLOCKEDLEFT){
        if(this->GetState() != WALKING_LEFT){
        
            this->context_->movementCounter = 0;
            this->SetState(WALKING_LEFT);
            this->SetDirection(LEFT);
            this->context_->movableObj_->WalkLeft(this->TurnPace());
        
        }

        if( speedFactor > this->context_->movementCounter ){
            this->context_->movementCounter++;
            this->context_->movableObj_->component->dx-=BLOCKWIDTH/speedFactor;  
            if(this->context_->movementCounter == speedFactor/2)
             this->context_->movableObj_->WalkLeft(this->TurnPace()); 
        }else{
            
            this->context_->movableObj_->component->SetColumn(this->context_->movableObj_->component->column - 1);
            this->context_->movementCounter = 0;
            this->SetState(TURN);
            this->context_->TransitionTo(new TurnState());
        }
    }else{
        this->SetState(TURN);
                this->context_->TransitionTo(new TurnState());
    } 
}

void WalkRight::Handle(int event){
    
    int speedFactor = this->GetSpeedFactor();
    
    if(NBLOCKEDRIGHT){

        if(this->GetState() != WALKING_RIGHT){
        
            this->context_->movementCounter = 0;
            this->SetState(WALKING_RIGHT);
            this->SetDirection(RIGHT);
            this->context_->movableObj_->WalkRight(this->TurnPace());
        
        }

        if( speedFactor > this->context_->movementCounter ){
            this->context_->movementCounter++;
            this->context_->movableObj_->component->dx+=BLOCKWIDTH/speedFactor; 
            if(this->context_->movementCounter == speedFactor/2)
             this->context_->movableObj_->WalkRight(this->TurnPace());  
        }else{
            
            this->context_->movableObj_->component->SetColumn(this->context_->movableObj_->component->column + 1); 
            this->context_->movementCounter = 0;
            this->SetState(TURN);
            this->context_->TransitionTo(new TurnState());
        }

    }else{
        this->SetState(TURN);
                this->context_->TransitionTo(new TurnState());
    } 
}

void Die::Handle(int event){
    
    if(this->GetState() != DYING){

        this->context_->movementCounter = 0;
        this->SetState(DYING);   

    }
    
    if(this->context_->movementCounter < DEATHCOUNTER){

        ++this->context_->movementCounter;        
        this->context_->movableObj_->Dies(this->context_->movementCounter/DEATHSTEP); 
          
    }else{ 

        this->context_->movementCounter = 0;        
        this->SetState(ERASED);

    }   

}