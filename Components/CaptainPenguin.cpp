#include "CaptainPenguin.h"

CaptainPenguin::CaptainPenguin(int row, int column): Movable(this), Mob(this){
    this->movementStateMachine = new MovementContext(new TurnState(), this, 0, DOWN);  
    Stage::GetSheet(this, 2);
    this->sx = CAPTAIN_PENGUIN_R_RP_SX;
    this->sy = CAPTAIN_PENGUIN_R_RP_SY;
    this->sh = CAPTAIN_PENGUIN_SH;
    this->sw = CAPTAIN_PENGUIN_SW;
    this->fStSx_ = CAPTAIN_PENGUIN_F_ST_SX;
    this->fStSy_ = CAPTAIN_PENGUIN_F_ST_SY;
    this->fLpSx_ = CAPTAIN_PENGUIN_F_LP_SX;
    this->fLpSy_ = CAPTAIN_PENGUIN_F_LP_SY;
    this->fRpSx_ = CAPTAIN_PENGUIN_F_RP_SX;
    this->fRpSy_ = CAPTAIN_PENGUIN_F_RP_SY;
    this->bStSx_ = CAPTAIN_PENGUIN_B_ST_SX;
    this->bStSy_ = CAPTAIN_PENGUIN_B_ST_SY;
    this->bRpSx_ = CAPTAIN_PENGUIN_B_RP_SX;
    this->bRpSy_ = CAPTAIN_PENGUIN_B_RP_SY;
    this->bLpSx_ = CAPTAIN_PENGUIN_B_LP_SX;
    this->bLpSy_ = CAPTAIN_PENGUIN_B_LP_SY;
    this->lStSx_ = CAPTAIN_PENGUIN_L_ST_SX;
    this->lStSy_ = CAPTAIN_PENGUIN_L_ST_SY;
    this->lRpSx_ = CAPTAIN_PENGUIN_L_RP_SX;
    this->lRpSy_ = CAPTAIN_PENGUIN_L_RP_SY;
    this->lLpSx_ = CAPTAIN_PENGUIN_L_LP_SX;
    this->lLpSy_ = CAPTAIN_PENGUIN_L_LP_SY;
    this->rStSx_ = CAPTAIN_PENGUIN_R_ST_SX;
    this->rStSy_ = CAPTAIN_PENGUIN_R_ST_SY;
    this->rRpSx_ = CAPTAIN_PENGUIN_R_RP_SX;
    this->rRpSy_ = CAPTAIN_PENGUIN_R_RP_SY;
    this->rLpSx_ = CAPTAIN_PENGUIN_R_LP_SX;
    this->rLpSy_ = CAPTAIN_PENGUIN_R_LP_SY;    
    this->dS1Sx_ = CAPTAIN_PENGUIN_D_S1_SX;
    this->dS1Sy_ = CAPTAIN_PENGUIN_D_S1_SY;
    this->dS2Sx_ = CAPTAIN_PENGUIN_D_S2_SX;
    this->dS2Sy_ = CAPTAIN_PENGUIN_D_S2_SY;
    this->dS3Sx_ = CAPTAIN_PENGUIN_D_S3_SX;
    this->dS3Sy_ = CAPTAIN_PENGUIN_D_S3_SY;
    Movable::SetMovements();
    this->DefineBlockPosition(row, column);  
    this->visitor = new CaptainPenguinVisitor(this);   
    Stage::visitorlist.push_back(this->visitor);      
    
} 

void CaptainPenguin::Accept(Visitor *visitor) const {
    visitor->VisitMob(this);
}

CaptainPenguinVisitor::CaptainPenguinVisitor(CaptainPenguin * captainPenguin){
    this->captainPenguin = captainPenguin;
}

void CaptainPenguinVisitor::VisitWall(const Wall *element) const{        
    
    this->captainPenguin->blockDown |= this->captainPenguin->BlockRow(element->component->row - 1, element->component->column );//blockleft
    this->captainPenguin->blockUp |= this->captainPenguin->BlockRow(element->component->row + 1, element->component->column );//blockright
    this->captainPenguin->blockRight |= this->captainPenguin->BlockColumn(element->component->column - 1, element->component->row);//blockdown
    this->captainPenguin->blockLeft |= this->captainPenguin->BlockColumn(element->component->column + 1, element->component->row);//blockup  

}

void CaptainPenguinVisitor::VisitMob(const Mob *element) const{

}

void CaptainPenguinVisitor::VisitBomb(const Bomb * element) const {
    
    if( this->captainPenguin->movementStateMachine->state != DYING  && 
        this->captainPenguin->movementStateMachine->state != ERASED &&        
        element->CheckIfHit(  
            this->captainPenguin->dy,
            this->captainPenguin->dy + (this->captainPenguin->sh),
            this->captainPenguin->dx,
            this->captainPenguin->dx + (this->captainPenguin->sw))
        ){
        this->captainPenguin->movementStateMachine->Request(DEAD);
        this->captainPenguin->hitByBomb = true;
    }else{
        this->captainPenguin->blockDown |= this->captainPenguin->BlockRow(element->row - 1, element->column );//blockleft
        this->captainPenguin->blockUp |= this->captainPenguin->BlockRow(element->row + 1, element->column );//blockright
        this->captainPenguin->blockRight |= this->captainPenguin->BlockColumn(element->column - 1, element->row);//blockdown
        this->captainPenguin->blockLeft |= this->captainPenguin->BlockColumn(element->column + 1, element->row);//blockup  
    }
}

  
CaptainPenguin::~CaptainPenguin(){
    
    delete this->movementStateMachine;        
    Visitor::RemoveVisitor( Stage::visitorlist, (Visitor *)this->visitor);    
    
}

void CaptainPenguin::Colide() {

}

int CaptainPenguin::GetEvent(int direction){
      
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

void CaptainPenguin::Move() {
        
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

void CaptainPenguin::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}