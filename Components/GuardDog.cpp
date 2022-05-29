#include "GuardDog.h"

GuardDog::GuardDog(int row, int column): Movable(this), Mob(this){
    this->movementStateMachine = new MovementContext(new TurnState(), this, 0, DOWN);  
    Stage::GetSheet(this, 1);
    this->sx = GUARD_DOG_D_S3_SX;
    this->sy = GUARD_DOG_D_S1_SY;
    this->sh = GUARD_DOG_SH;
    this->sw = GUARD_DOG_SW;
    this->fStSx_ = GUARD_DOG_F_ST_SX;
    this->fStSy_ = GUARD_DOG_F_ST_SY;
    this->fLpSx_ = GUARD_DOG_F_LP_SX;
    this->fLpSy_ = GUARD_DOG_F_LP_SY;
    this->fRpSx_ = GUARD_DOG_F_RP_SX;
    this->fRpSy_ = GUARD_DOG_F_RP_SY;
    this->bStSx_ = GUARD_DOG_B_ST_SX;
    this->bStSy_ = GUARD_DOG_B_ST_SY;
    this->bRpSx_ = GUARD_DOG_B_RP_SX;
    this->bRpSy_ = GUARD_DOG_B_RP_SY;
    this->bLpSx_ = GUARD_DOG_B_LP_SX;
    this->bLpSy_ = GUARD_DOG_B_LP_SY;
    this->lStSx_ = GUARD_DOG_L_ST_SX;
    this->lStSy_ = GUARD_DOG_L_ST_SY;
    this->lRpSx_ = GUARD_DOG_L_RP_SX;
    this->lRpSy_ = GUARD_DOG_L_RP_SY;
    this->lLpSx_ = GUARD_DOG_L_Lp_SX;
    this->lLpSy_ = GUARD_DOG_L_LP_SY;
    this->rStSx_ = GUARD_DOG_R_ST_SX;
    this->rStSy_ = GUARD_DOG_R_ST_SY;
    this->rRpSx_ = GUARD_DOG_R_RP_SX;
    this->rRpSy_ = GUARD_DOG_R_RP_SY;
    this->rLpSx_ = GUARD_DOG_R_LP_SX;
    this->rLpSy_ = GUARD_DOG_R_LP_SY;    
    this->dS1Sx_ = GUARD_DOG_D_S1_SX;
    this->dS1Sy_ = GUARD_DOG_D_S1_SY;
    this->dS2Sx_ = GUARD_DOG_D_S2_SX;
    this->dS2Sy_ = GUARD_DOG_D_S2_SY;
    this->dS3Sx_ = GUARD_DOG_D_S3_SX;
    this->dS3Sy_ = GUARD_DOG_D_S3_SY;
    Movable::SetMovements();
    this->DefineBlockPosition(row, column);  
    this->visitor = new GuardDogVisitor(this);   
    Stage::visitorlist.push_back(this->visitor);      
    
} 

void GuardDog::Accept(Visitor *visitor) const {
    visitor->VisitMob(this);
}

GuardDogVisitor::GuardDogVisitor(GuardDog * guardDog){
    this->guardDog = guardDog;
}

void GuardDogVisitor::VisitWall(const Wall *element) const{        
    
    this->guardDog->blockDown |= this->guardDog->BlockRow(element->component->row - 1, element->component->column );//blockleft
    this->guardDog->blockUp |= this->guardDog->BlockRow(element->component->row + 1, element->component->column );//blockright
    this->guardDog->blockRight |= this->guardDog->BlockColumn(element->component->column - 1, element->component->row);//blockdown
    this->guardDog->blockLeft |= this->guardDog->BlockColumn(element->component->column + 1, element->component->row);//blockup  

}

void GuardDogVisitor::VisitMob(const Mob *element) const{

}

void GuardDogVisitor::VisitBomb(const Bomb * element) const {
    
    if( this->guardDog->movementStateMachine->state != DYING  && 
        this->guardDog->movementStateMachine->state != ERASED &&        
        element->CheckIfHit(  
            this->guardDog->dy,
            this->guardDog->dy + (this->guardDog->sh),
            this->guardDog->dx,
            this->guardDog->dx + (this->guardDog->sw))
        ){
        this->guardDog->movementStateMachine->Request(DEAD);
    }else{
        this->guardDog->blockDown |= this->guardDog->BlockRow(element->row - 1, element->column );//blockleft
        this->guardDog->blockUp |= this->guardDog->BlockRow(element->row + 1, element->column );//blockright
        this->guardDog->blockRight |= this->guardDog->BlockColumn(element->column - 1, element->row);//blockdown
        this->guardDog->blockLeft |= this->guardDog->BlockColumn(element->column + 1, element->row);//blockup  
    }
}

  
GuardDog::~GuardDog(){
    
    delete this->movementStateMachine;        
    Visitor::RemoveVisitor( Stage::visitorlist, (Visitor *)this->visitor);    
    
}

void GuardDog::Colide() {

}

int GuardDog::GetEvent(int direction){
      
    vector<int> allowedDirections;
    
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

void GuardDog::Move() {
    
        int event;

        if(this->movementStateMachine->state == ERASED){

            this->removed = true;

        }else if(this->movementStateMachine->state == DYING){
            
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

void GuardDog::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}