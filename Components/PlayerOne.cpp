#include "PlayerOne.h"

PlayerOne::PlayerOne(int row, int column): Movable(this){

    this->movementStateMachine = new MovementContext(new TurnState(), this, this->speed, UP);  
    this->sh = P_ONE_SH;
    this->sw = P_ONE_SW; 
    this->fStSx_ = P_ONE_F_ST_SX;
    this->fStSy_ = P_ONE_F_ST_SY;
    this->fLpSx_ = P_ONE_F_LP_SX;
    this->fLpSy_ = P_ONE_F_LP_SY;
    this->fRpSx_ = P_ONE_F_RP_SX;
    this->fRpSy_ = P_ONE_F_RP_SY;
    this->bStSx_ = P_ONE_B_ST_SX;
    this->bStSy_ = P_ONE_B_ST_SY;
    this->bRpSx_ = P_ONE_B_RP_SX;
    this->bRpSy_ = P_ONE_B_RP_SY;
    this->bLpSx_ = P_ONE_B_LP_SX;
    this->bLpSy_ = P_ONE_B_LP_SY;
    this->lStSx_ = P_ONE_L_ST_SX;
    this->lStSy_ = P_ONE_L_ST_SY;
    this->lRpSx_ = P_ONE_L_RP_SX;
    this->lRpSy_ = P_ONE_L_RP_SY;
    this->lLpSx_ = P_ONE_L_Lp_SX;
    this->lLpSy_ = P_ONE_L_LP_SY;
    this->rStSx_ = P_ONE_R_ST_SX;
    this->rStSy_ = P_ONE_R_ST_SY;
    this->rRpSx_ = P_ONE_R_RP_SX;
    this->rRpSy_ = P_ONE_R_RP_SY;
    this->rLpSx_ = P_ONE_R_LP_SX;
    this->rLpSy_ = P_ONE_R_LP_SY;
    this->dS1Sx_ = P_ONE_D_S1_SX;
    this->dS1Sy_ = P_ONE_D_S1_SY;
    this->dS2Sx_ = P_ONE_D_S2_SX;
    this->dS2Sy_ = P_ONE_D_S2_SY;
    this->dS3Sx_ = P_ONE_D_S3_SX;
    this->dS3Sy_ = P_ONE_D_S3_SY;

    Movable::SetMovements();
    this->initialColumn = column;
    this->initialRow    = row;
    this->DefineBlockPosition(row, column);  
    this->visitor = new PlayerOneVisitor(this);   
    Stage::visitorlist.push_back(this->visitor);  
    this->observer = new PlayerObserver(* Stage::playerSubject);

    UpdatePlayerStatus;
    
} 

void PlayerOne::FinishStage(){
    Stage::eventsObserver->Update(FINISHSTAGE);
}

void PlayerOne::Accept(Visitor *visitor) const {

    visitor->VisitPlayerOne(this);

}

PlayerOneVisitor::PlayerOneVisitor(PlayerOne * player){

    this->player = player;

}

void PlayerOneVisitor::VisitWall(const Wall *element) const{    
    
    this->player->blockDown |= this->player->BlockRow(element->component->row - 1, element->component->column );//blockleft
    this->player->blockUp |= this->player->BlockRow(element->component->row + 1, element->component->column );//blockright
    this->player->blockRight |= this->player->BlockColumn(element->component->column - 1, element->component->row);//blockdown
    this->player->blockLeft |= this->player->BlockColumn(element->component->column + 1, element->component->row);//blockup  

}

void PlayerOneVisitor::VisitMob(const Mob *element) const{
    
    if( this->player->movementStateMachine->state != DYING  && 
        this->player->movementStateMachine->state != ERASED &&
        element->component->column == this->player->column  &&
        element->component->row == this->player->row ){
           this->player->movementStateMachine->state = DYING;
           //printf("teste %d\n",this->player->movementStateMachine->state);
           Stage::eventsObserver->Update(DEAD);
    }

}

void PlayerOneVisitor::VisitBomb(const Bomb * element) const {    
    if( this->player->movementStateMachine->state != DYING  && 
        this->player->movementStateMachine->state != ERASED &&        
        element->CheckIfHit(
            this->player->dy,
            this->player->dy + (this->player->sh),
            this->player->dx,
            this->player->dx + (this->player->sw))
        ){
        this->player->movementStateMachine->state = DYING;        
        Stage::eventsObserver->Update(DEAD);
    }else{
        this->player->blockDown |= this->player->BlockRow(element->row - 1, element->column );//blockleft
        this->player->blockUp |= this->player->BlockRow(element->row + 1, element->column );//blockright
        this->player->blockRight |= this->player->BlockColumn(element->column - 1, element->row);//blockdown
        this->player->blockLeft |= this->player->BlockColumn(element->column + 1, element->row);//blockup  
    }
}

void PlayerOne::AddLife(){
    if(this->life < 3)
        this->life ++;
}

void PlayerOne::AddBombStrenhth(){
    if(this->bombStrength < 3)
        this->bombStrength ++;
}

void PlayerOne::AddSpeed(){
   if(this->speed < MAXIMUMSPEED)
   {
         this->speed += 2;
         this->movementStateMachine->speed +=4;
   }

}

void PlayerOne::AddNoOfBombs(){
    if(this->nOBombs < 3)
        this->nOBombs ++;
}

  
PlayerOne::~PlayerOne(){
    

    delete this->movementStateMachine;
    Visitor::RemoveVisitor( Stage::visitorlist, (Visitor *)this->visitor);
    /*
    for(vector<Visitor *>::iterator it = Stage::visitorlist.begin(); it!=Stage::visitorlist.end();){
        
        if((*it) == ((Visitor *)this->visitor)){
            delete * it;  
            it = Stage::visitorlist.erase(it);
        }
        else {
            ++it;
        }
        
    }*/
    
}

void PlayerOne::Colide() {

}

void PlayerOne::Move() {

    UpdatePlayerStatus;

    int event = Stage::eventsObserver->GetEvent();
    
    if(this->movementStateMachine->state == DYING){

        movementStateMachine->Request(DEAD);

    }if(this->movementStateMachine->state == ERASED){
        
        if(this->life == 0){

            Stage::eventsObserver->Update(PLAYER_GAMEOVER);

        }else{

            --this->life;            
            this->row    = this->initialRow;
            this->column = this->initialColumn;
            this->speed = INITIAL_SPEED;
            this->DefineBlockPosition(this->row, this->column);
            delete this->movementStateMachine;
            this->movementStateMachine = new MovementContext(new TurnState(), this, this->speed, UP);

        }

    }else if(event >= 0){        

        switch (event)
        {
            case UP:
                this->movementStateMachine->Request(UP);
                break;
            case DOWN:
                 this->movementStateMachine->Request(DOWN);
                break;
            case LEFT:
                 this->movementStateMachine->Request(LEFT);
                break;
            case RIGHT:
                 this->movementStateMachine->Request(RIGHT);
                break;            
            case DEAD:
                this->movementStateMachine->Request(DEAD);
                break;
            default:
                this->movementStateMachine->Request(IDDLE);
                break;
        }

    }else {

        this->movementStateMachine->Request(IDDLE);
        
    }

}

void PlayerOne::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}