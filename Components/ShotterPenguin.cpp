#include "ShotterPenguin.h"

ShotterPenguin::ShotterPenguin(int row, int column): Movable(this), Mob(this){
    this->movementStateMachine = new MovementContext(new TurnState(), this, 4, DOWN);  
    Stage::GetSheet(this, 2);
    this->sx = SHOTTER_PENGUIN_D_S1_SX;
    this->sy = SHOTTER_PENGUIN_D_S3_SY;
    this->sh = SHOTTER_PENGUIN_SH;
    this->sw = SHOTTER_PENGUIN_SW;
    this->fStSx_ = SHOTTER_PENGUIN_F_ST_SX;
    this->fStSy_ = SHOTTER_PENGUIN_F_ST_SY;
    this->fLpSx_ = SHOTTER_PENGUIN_F_LP_SX;
    this->fLpSy_ = SHOTTER_PENGUIN_F_LP_SY;
    this->fRpSx_ = SHOTTER_PENGUIN_F_RP_SX;
    this->fRpSy_ = SHOTTER_PENGUIN_F_RP_SY;
    this->bStSx_ = SHOTTER_PENGUIN_B_ST_SX;
    this->bStSy_ = SHOTTER_PENGUIN_B_ST_SY;
    this->bRpSx_ = SHOTTER_PENGUIN_B_RP_SX;
    this->bRpSy_ = SHOTTER_PENGUIN_B_RP_SY;
    this->bLpSx_ = SHOTTER_PENGUIN_B_LP_SX;
    this->bLpSy_ = SHOTTER_PENGUIN_B_LP_SY;
    this->lStSx_ = SHOTTER_PENGUIN_L_ST_SX;
    this->lStSy_ = SHOTTER_PENGUIN_L_ST_SY;
    this->lRpSx_ = SHOTTER_PENGUIN_L_RP_SX;
    this->lRpSy_ = SHOTTER_PENGUIN_L_RP_SY;
    this->lLpSx_ = SHOTTER_PENGUIN_L_LP_SX;
    this->lLpSy_ = SHOTTER_PENGUIN_L_LP_SY;
    this->rStSx_ = SHOTTER_PENGUIN_R_ST_SX;
    this->rStSy_ = SHOTTER_PENGUIN_R_ST_SY;
    this->rRpSx_ = SHOTTER_PENGUIN_R_RP_SX;
    this->rRpSy_ = SHOTTER_PENGUIN_R_RP_SY;
    this->rLpSx_ = SHOTTER_PENGUIN_R_LP_SX;
    this->rLpSy_ = SHOTTER_PENGUIN_R_LP_SY;    
    this->dS1Sx_ = SHOTTER_PENGUIN_D_S1_SX;
    this->dS1Sy_ = SHOTTER_PENGUIN_D_S1_SY;
    this->dS2Sx_ = SHOTTER_PENGUIN_D_S2_SX;
    this->dS2Sy_ = SHOTTER_PENGUIN_D_S2_SY;
    this->dS3Sx_ = SHOTTER_PENGUIN_D_S3_SX;
    this->dS3Sy_ = SHOTTER_PENGUIN_D_S3_SY;
    Movable::SetMovements();
    this->DefineBlockPosition(row, column);  
    this->visitor = new ShotterPenguinVisitor(this);   
    Stage::visitorlist.push_back(this->visitor);      
    
} 

void ShotterPenguin::Accept(Visitor *visitor) const {
    visitor->VisitMob(this);
}

ShotterPenguinVisitor::ShotterPenguinVisitor(ShotterPenguin * shotterPenguin){
    this->shotterPenguin = shotterPenguin;
}

void ShotterPenguinVisitor::VisitWall(const Wall *element) const{        
    
    this->shotterPenguin->blockDown |= this->shotterPenguin->BlockRow(element->component->row - 1, element->component->column );//blockleft
    this->shotterPenguin->blockUp |= this->shotterPenguin->BlockRow(element->component->row + 1, element->component->column );//blockright
    this->shotterPenguin->blockRight |= this->shotterPenguin->BlockColumn(element->component->column - 1, element->component->row);//blockdown
    this->shotterPenguin->blockLeft |= this->shotterPenguin->BlockColumn(element->component->column + 1, element->component->row);//blockup  

}

void ShotterPenguinVisitor::VisitMob(const Mob *element) const{

}
void ShotterPenguinVisitor::VisitPlayerOne(const PlayerOne *player) const{
   this->shotterPenguin->playerColumn = player->column; 
   this->shotterPenguin->playerRow    = player->row;    
}

void ShotterPenguinVisitor::VisitBomb(const Bomb * element) const {
    
    if( this->shotterPenguin->movementStateMachine->state != DYING  && 
        this->shotterPenguin->movementStateMachine->state != ERASED &&        
        element->CheckIfHit(  
            this->shotterPenguin->dy,
            this->shotterPenguin->dy + (this->shotterPenguin->sh),
            this->shotterPenguin->dx,
            this->shotterPenguin->dx + (this->shotterPenguin->sw))
        ){
        this->shotterPenguin->movementStateMachine->Request(DEAD);
        this->shotterPenguin->hitByBomb = true;
    }else{
        this->shotterPenguin->blockDown |= this->shotterPenguin->BlockRow(element->row - 1, element->column );//blockleft
        this->shotterPenguin->blockUp |= this->shotterPenguin->BlockRow(element->row + 1, element->column );//blockright
        this->shotterPenguin->blockRight |= this->shotterPenguin->BlockColumn(element->column - 1, element->row);//blockdown
        this->shotterPenguin->blockLeft |= this->shotterPenguin->BlockColumn(element->column + 1, element->row);//blockup  
    }
}

  
ShotterPenguin::~ShotterPenguin(){
    
    delete this->movementStateMachine;        
    Visitor::RemoveVisitor( Stage::visitorlist, (Visitor *)this->visitor);    
    
}

void ShotterPenguin::Colide() {

}

int ShotterPenguin::PrepareShot(){

    if(this->waiting){
        this->shotTimer --;
        if(this->shotTimer == SHOT_TIME)
            Stage::componentQueue.push_back(new FishBullet(this->row, this->column, this->movementStateMachine->direction));
        if(this->shotTimer == 0)
            this->waiting = false;
        return IDDLE;
    }else{
        if(this->shotTimer < SHOT_INTERVAL)
            this->shotTimer ++;
    }
    
    if(this->column == playerColumn){
        if(!this->blockDown 
        && this->shotTimer == SHOT_INTERVAL
        && this->playerRow > this->row 
        && this->movementStateMachine->direction == DOWN
        ){
           this->shotTimer --;
           this->waiting = true;           
           return IDDLE; 
        }

        if(!this->blockUp 
        && this->shotTimer == SHOT_INTERVAL
        && this->playerRow < this->row 
        && this->movementStateMachine->direction == UP
        ){
           this->shotTimer --;
           this->waiting = true;           
           return IDDLE; 
        }

        if(!this->blockDown && this->playerRow > this->row)
            return DOWN;
        if(!this->blockUp && this->playerRow < this->row)
            return UP;
    }

    if(this->row == playerRow){
        
        if(!this->blockRight 
        && this->shotTimer == SHOT_INTERVAL
        && this->playerColumn > this->column 
        && this->movementStateMachine->direction == RIGHT
        ){
           this->shotTimer --;
           this->waiting = true;           
           return IDDLE; 
        }

        if(!this->blockLeft
        && this->shotTimer == SHOT_INTERVAL
        && this->playerColumn < this->column 
        && this->movementStateMachine->direction == LEFT
        ){
           this->shotTimer --;
           this->waiting = true;           
           return IDDLE; 
        }
        
        if(!this->blockRight && this->playerColumn > this->column)
            return RIGHT;
        if(!this->blockLeft  && this->playerColumn < this->column)
            return LEFT;
    }

    return -2;
}

int ShotterPenguin::GetEvent(int direction){
      
    vector<int> allowedDirections;
    int shotMovement = this->PrepareShot();

    if( shotMovement > -2)
        return shotMovement;
    
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

void ShotterPenguin::Move() {
        
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

void ShotterPenguin::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}