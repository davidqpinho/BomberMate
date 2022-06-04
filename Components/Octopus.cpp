#include "Octopus.h"

Octopus::Octopus(int row, int column): Movable(this), Mob(this){
    this->movementStateMachine = new MovementContext(new TurnState(), this, 0, DOWN);  
    Stage::GetSheet(this, 1);
    this->sx = OCTOPUS_D_S3_SX;
    this->sy = OCTOPUS_D_S3_SY;
    this->sh = OCTOPUS_SH;
    this->sw = OCTOPUS_SW;
    this->fStSx_ = OCTOPUS_F_ST_SX;
    this->fStSy_ = OCTOPUS_F_ST_SY;
    this->fLpSx_ = OCTOPUS_F_LP_SX;
    this->fLpSy_ = OCTOPUS_F_LP_SY;
    this->fRpSx_ = OCTOPUS_F_RP_SX;
    this->fRpSy_ = OCTOPUS_F_RP_SY;
    this->bStSx_ = OCTOPUS_B_ST_SX;
    this->bStSy_ = OCTOPUS_B_ST_SY;
    this->bRpSx_ = OCTOPUS_B_RP_SX;
    this->bRpSy_ = OCTOPUS_B_RP_SY;
    this->bLpSx_ = OCTOPUS_B_LP_SX;
    this->bLpSy_ = OCTOPUS_B_LP_SY;
    this->lStSx_ = OCTOPUS_L_ST_SX;
    this->lStSy_ = OCTOPUS_L_ST_SY;
    this->lRpSx_ = OCTOPUS_L_RP_SX;
    this->lRpSy_ = OCTOPUS_L_RP_SY;
    this->lLpSx_ = OCTOPUS_L_LP_SX;
    this->lLpSy_ = OCTOPUS_L_LP_SY;
    this->rStSx_ = OCTOPUS_R_ST_SX;
    this->rStSy_ = OCTOPUS_R_ST_SY;
    this->rRpSx_ = OCTOPUS_R_RP_SX;
    this->rRpSy_ = OCTOPUS_R_RP_SY;
    this->rLpSx_ = OCTOPUS_R_LP_SX;
    this->rLpSy_ = OCTOPUS_R_LP_SY;    
    this->dS1Sx_ = OCTOPUS_D_S1_SX;
    this->dS1Sy_ = OCTOPUS_D_S1_SY;
    this->dS2Sx_ = OCTOPUS_D_S2_SX;
    this->dS2Sy_ = OCTOPUS_D_S2_SY;
    this->dS3Sx_ = OCTOPUS_D_S3_SX;
    this->dS3Sy_ = OCTOPUS_D_S3_SY;
    Movable::SetMovements();
    this->DefineBlockPosition(row, column);  
    this->visitor = new OctopusVisitor(this);   
    Stage::visitorlist.push_back(this->visitor);      
    
} 

void Octopus::Accept(Visitor *visitor) const {
    visitor->VisitMob(this);
}

OctopusVisitor::OctopusVisitor(Octopus * octopus){
    this->octopus = octopus;
}

void OctopusVisitor::VisitWall(const Wall *element) const{        
    
    this->octopus->blockDown |= this->octopus->BlockRow(element->component->row - 1, element->component->column );//blockleft
    this->octopus->blockUp |= this->octopus->BlockRow(element->component->row + 1, element->component->column );//blockright
    this->octopus->blockRight |= this->octopus->BlockColumn(element->component->column - 1, element->component->row);//blockdown
    this->octopus->blockLeft |= this->octopus->BlockColumn(element->component->column + 1, element->component->row);//blockup  

}

void OctopusVisitor::VisitMob(const Mob *element) const{

}

void OctopusVisitor::VisitBomb(const Bomb * element) const {
    
    if( this->octopus->movementStateMachine->state != DYING  && 
        this->octopus->movementStateMachine->state != ERASED &&        
        element->CheckIfHit(  
            this->octopus->dy,
            this->octopus->dy + (this->octopus->sh),
            this->octopus->dx,
            this->octopus->dx + (this->octopus->sw))
        ){
        this->octopus->movementStateMachine->Request(DEAD);
        this->octopus->hitByBomb = true;
    }else{
        this->octopus->blockDown |= this->octopus->BlockRow(element->row - 1, element->column );//blockleft
        this->octopus->blockUp |= this->octopus->BlockRow(element->row + 1, element->column );//blockright
        this->octopus->blockRight |= this->octopus->BlockColumn(element->column - 1, element->row);//blockdown
        this->octopus->blockLeft |= this->octopus->BlockColumn(element->column + 1, element->row);//blockup  
    }
}

  
Octopus::~Octopus(){
    
    delete this->movementStateMachine;        
    Visitor::RemoveVisitor( Stage::visitorlist, (Visitor *)this->visitor);    
    
}

void Octopus::Colide() {

}

int Octopus::GetEvent(int direction){
      
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

void Octopus::Move() {
        
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

void Octopus::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}