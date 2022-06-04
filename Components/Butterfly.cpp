#include "Butterfly.h"

Butterfly::Butterfly(int row, int column): Movable(this), Mob(this){
    this->movementStateMachine = new MovementContext(new TurnState(), this, 0, DOWN);  
    this->zpos = 10;
    Stage::GetSheet(this, 1);
    this->sx = BUTTERFLY_D_S3_SX;
    this->sy = BUTTERFLY_D_S3_SY;
    this->sh = BUTTERFLY_SH;
    this->sw = BUTTERFLY_SW;
    this->fStSx_ = BUTTERFLY_F_ST_SX;
    this->fStSy_ = BUTTERFLY_F_ST_SY;
    this->fLpSx_ = BUTTERFLY_F_LP_SX;
    this->fLpSy_ = BUTTERFLY_F_LP_SY;
    this->fRpSx_ = BUTTERFLY_F_RP_SX;
    this->fRpSy_ = BUTTERFLY_F_RP_SY;
    this->bStSx_ = BUTTERFLY_B_ST_SX;
    this->bStSy_ = BUTTERFLY_B_ST_SY;
    this->bRpSx_ = BUTTERFLY_B_RP_SX;
    this->bRpSy_ = BUTTERFLY_B_RP_SY;
    this->bLpSx_ = BUTTERFLY_B_LP_SX;
    this->bLpSy_ = BUTTERFLY_B_LP_SY;
    this->lStSx_ = BUTTERFLY_L_ST_SX;
    this->lStSy_ = BUTTERFLY_L_ST_SY;
    this->lRpSx_ = BUTTERFLY_L_RP_SX;
    this->lRpSy_ = BUTTERFLY_L_RP_SY;
    this->lLpSx_ = BUTTERFLY_L_Lp_SX;
    this->lLpSy_ = BUTTERFLY_L_LP_SY;
    this->rStSx_ = BUTTERFLY_R_ST_SX;
    this->rStSy_ = BUTTERFLY_R_ST_SY;
    this->rRpSx_ = BUTTERFLY_R_RP_SX;
    this->rRpSy_ = BUTTERFLY_R_RP_SY;
    this->rLpSx_ = BUTTERFLY_R_LP_SX;
    this->rLpSy_ = BUTTERFLY_R_LP_SY;    
    this->dS1Sx_ = BUTTERFLY_D_S1_SX;
    this->dS1Sy_ = BUTTERFLY_D_S1_SY;
    this->dS2Sx_ = BUTTERFLY_D_S2_SX;
    this->dS2Sy_ = BUTTERFLY_D_S2_SY;
    this->dS3Sx_ = BUTTERFLY_D_S3_SX;
    this->dS3Sy_ = BUTTERFLY_D_S3_SY;
    Movable::SetMovements();
    this->DefineBlockPosition(row, column);  
    this->visitor = new ButterflyVisitor(this);   
    Stage::visitorlist.push_back(this->visitor);      
    
} 

void Butterfly::Accept(Visitor *visitor) const {
    visitor->VisitMob(this);
}

ButterflyVisitor::ButterflyVisitor(Butterfly * butterfly){
    this->butterfly = butterfly;
}

void ButterflyVisitor::VisitWall(const Wall *element) const{        
    
    this->butterfly->blockDown |= this->butterfly->BlockRow(element->component->row - 1, element->component->column );//blockleft
    this->butterfly->blockUp |= this->butterfly->BlockRow(element->component->row + 1, element->component->column );//blockright
    this->butterfly->blockRight |= this->butterfly->BlockColumn(element->component->column - 1, element->component->row);//blockdown
    this->butterfly->blockLeft |= this->butterfly->BlockColumn(element->component->column + 1, element->component->row);//blockup  

}

void ButterflyVisitor::VisitMob(const Mob *element) const{

}

void ButterflyVisitor::VisitBomb(const Bomb * element) const {
    
    if( this->butterfly->movementStateMachine->state != DYING  && 
        this->butterfly->movementStateMachine->state != ERASED &&        
        element->CheckIfHit(  
            this->butterfly->dy,
            this->butterfly->dy + (this->butterfly->sh),
            this->butterfly->dx,
            this->butterfly->dx + (this->butterfly->sw))
        ){
        this->butterfly->movementStateMachine->Request(DEAD);
        this->butterfly->hitByBomb = true;
        
    }
}

  
Butterfly::~Butterfly(){
    
    delete this->movementStateMachine;        
    Visitor::RemoveVisitor( Stage::visitorlist, (Visitor *)this->visitor);    
    
}

void Butterfly::Colide() {

}

int Butterfly::GetEvent(int direction){
      
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

void Butterfly::Move() {
        
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

void Butterfly::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}