#include "JellyGirl.h"

JellyGirl::JellyGirl(int row, int column): Movable(this), Mob(this){
    this->movementStateMachine = new MovementContext(new TurnState(), this, 0, DOWN);  
    Stage::GetSheet(this, 1);
    this->sx = JELLY_GIRL_D_S2_SX;
    this->sy = JELLY_GIRL_D_S2_SY;
    this->sh = JELLY_GIRL_SH;
    this->sw = JELLY_GIRL_SW;
    this->fStSx_ = JELLY_GIRL_F_ST_SX;
    this->fStSy_ = JELLY_GIRL_F_ST_SY;
    this->fLpSx_ = JELLY_GIRL_F_LP_SX;
    this->fLpSy_ = JELLY_GIRL_F_LP_SY;
    this->fRpSx_ = JELLY_GIRL_F_RP_SX;
    this->fRpSy_ = JELLY_GIRL_F_RP_SY;
    this->bStSx_ = JELLY_GIRL_B_ST_SX;
    this->bStSy_ = JELLY_GIRL_B_ST_SY;
    this->bRpSx_ = JELLY_GIRL_B_RP_SX;
    this->bRpSy_ = JELLY_GIRL_B_RP_SY;
    this->bLpSx_ = JELLY_GIRL_B_LP_SX;
    this->bLpSy_ = JELLY_GIRL_B_LP_SY;
    this->lStSx_ = JELLY_GIRL_L_ST_SX;
    this->lStSy_ = JELLY_GIRL_L_ST_SY;
    this->lRpSx_ = JELLY_GIRL_L_RP_SX;
    this->lRpSy_ = JELLY_GIRL_L_RP_SY;
    this->lLpSx_ = JELLY_GIRL_L_LP_SX;
    this->lLpSy_ = JELLY_GIRL_L_LP_SY;
    this->rStSx_ = JELLY_GIRL_R_ST_SX;
    this->rStSy_ = JELLY_GIRL_R_ST_SY;
    this->rRpSx_ = JELLY_GIRL_R_RP_SX;
    this->rRpSy_ = JELLY_GIRL_R_RP_SY;
    this->rLpSx_ = JELLY_GIRL_R_LP_SX;
    this->rLpSy_ = JELLY_GIRL_R_LP_SY;    
    this->dS1Sx_ = JELLY_GIRL_D_S1_SX;
    this->dS1Sy_ = JELLY_GIRL_D_S1_SY;
    this->dS2Sx_ = JELLY_GIRL_D_S2_SX;
    this->dS2Sy_ = JELLY_GIRL_D_S2_SY;
    this->dS3Sx_ = JELLY_GIRL_D_S3_SX;
    this->dS3Sy_ = JELLY_GIRL_D_S3_SY;
    Movable::SetMovements();
    this->DefineBlockPosition(row, column);  
    this->visitor = new JellyGirlVisitor(this);   
    Stage::visitorlist.push_back(this->visitor);      
    
} 

void JellyGirl::Accept(Visitor *visitor) const {
    visitor->VisitMob(this);
}

JellyGirlVisitor::JellyGirlVisitor(JellyGirl * jellyGirl){
    this->jellyGirl = jellyGirl;
}

void JellyGirlVisitor::VisitWall(const Wall *element) const{        
    
    this->jellyGirl->blockDown |= this->jellyGirl->BlockRow(element->component->row - 1, element->component->column );//blockleft
    this->jellyGirl->blockUp |= this->jellyGirl->BlockRow(element->component->row + 1, element->component->column );//blockright
    this->jellyGirl->blockRight |= this->jellyGirl->BlockColumn(element->component->column - 1, element->component->row);//blockdown
    this->jellyGirl->blockLeft |= this->jellyGirl->BlockColumn(element->component->column + 1, element->component->row);//blockup  

}

void JellyGirlVisitor::VisitMob(const Mob *element) const{

}

void JellyGirlVisitor::VisitPlayerOne(const PlayerOne *player) const{
   this->jellyGirl->playerColumn = player->column; 
   this->jellyGirl->playerRow    = player->row;    
}

void JellyGirlVisitor::VisitBomb(const Bomb * element) const {
    
    if( this->jellyGirl->movementStateMachine->state != DYING  && 
        this->jellyGirl->movementStateMachine->state != ERASED &&        
        element->CheckIfHit(  
            this->jellyGirl->dy,
            this->jellyGirl->dy + (this->jellyGirl->sh),
            this->jellyGirl->dx,
            this->jellyGirl->dx + (this->jellyGirl->sw))
        ){
        this->jellyGirl->movementStateMachine->Request(DEAD);
        this->jellyGirl->hitByBomb = true;
    }else{
        this->jellyGirl->blockDown |= this->jellyGirl->BlockRow(element->row - 1, element->column );//blockleft
        this->jellyGirl->blockUp |= this->jellyGirl->BlockRow(element->row + 1, element->column );//blockright
        this->jellyGirl->blockRight |= this->jellyGirl->BlockColumn(element->column - 1, element->row);//blockdown
        this->jellyGirl->blockLeft |= this->jellyGirl->BlockColumn(element->column + 1, element->row);//blockup  
    }
}

  
JellyGirl::~JellyGirl(){
    
    delete this->movementStateMachine;        
    Visitor::RemoveVisitor( Stage::visitorlist, (Visitor *)this->visitor);    
    
}

void JellyGirl::Colide() {

}

int JellyGirl::GetEvent(int direction){
      
    vector<int> allowedDirections;

    if(this->column == playerColumn){
        if(!this->blockDown && this->playerRow > this->row)
            return DOWN;
        if(!this->blockUp && this->playerRow < this->row)
            return UP;
    }

    if(this->row == playerRow){
        if(!this->blockRight && this->playerColumn > this->column)
            return RIGHT;
        if(!this->blockLeft  && this->playerColumn < this->column)
            return LEFT;
    }
    
    if(!this->blockUp) allowedDirections.push_back(UP); 
    if(!this->blockDown) allowedDirections.push_back(DOWN); 
    if(!this->blockLeft) allowedDirections.push_back(LEFT); 
    if(!this->blockRight) allowedDirections.push_back(RIGHT); 
    
    switch (direction)
    {
        case UP:
            return (this->blockUp)? NewRandomNumber(&allowedDirections): direction;
        case DOWN:
            return (this->blockDown)? NewRandomNumber(&allowedDirections): direction;           
        case LEFT:
            return (this->blockLeft)? NewRandomNumber(&allowedDirections): direction;  
        case RIGHT:             
            return (this->blockRight)? NewRandomNumber(&allowedDirections): direction;
    }   

}

void JellyGirl::Move() {
        
        int event;

        if(this->movementStateMachine->state == ERASED){

            this->removed = true;

        }else if(this->hitByBomb || this->movementStateMachine->state == DYING){
            
            movementStateMachine->Request(DEAD);

        }else{

            event = GetEvent(this->movementStateMachine->direction);
                    
            switch (event)
            {
                case UP:
                    movementStateMachine->Request(UP);
                    break;
                case DOWN:
                    movementStateMachine->Request(DOWN);
                    break;
                case LEFT:
                    movementStateMachine->Request(LEFT);
                    break;
                case RIGHT:
                    movementStateMachine->Request(RIGHT);
                    break;            
                default:
                    movementStateMachine->Request(IDDLE);
                    break;
            }  

        }
    
}

void JellyGirl::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}