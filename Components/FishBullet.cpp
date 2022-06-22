#include "FishBullet.h"

FishBullet::FishBullet(int row, int column, int direction): Movable(this), Mob(this){
    
    this->direction = direction;
    this->movementStateMachine = new MovementContext(new TurnState(), this, 10, DOWN);  
    Stage::GetSheet(this, 3);
    
    switch(direction){
        case UP:
            this->sx = FISH_BULLET_B_ST_SX;
            this->sy = FISH_BULLET_B_ST_SY;
            this->fStSx_ = FISH_BULLET_B_ST_SX;
            this->fStSy_ = FISH_BULLET_B_ST_SY;
        break;
        case DOWN:
            this->sx = FISH_BULLET_F_ST_SX;
            this->sy = FISH_BULLET_F_ST_SY;
            this->fStSx_ = FISH_BULLET_F_ST_SX;
            this->fStSy_ = FISH_BULLET_F_ST_SY;
        break;
        case RIGHT:
            this->sx = FISH_BULLET_R_ST_SX;
            this->sy = FISH_BULLET_R_ST_SY;
            this->fStSx_ = FISH_BULLET_R_ST_SX;
            this->fStSy_ = FISH_BULLET_R_ST_SY;
        break;
        case LEFT:
            this->sx = FISH_BULLET_L_ST_SX;
            this->sy = FISH_BULLET_L_ST_SY;
            this->fStSx_ = FISH_BULLET_L_ST_SX;
            this->fStSy_ = FISH_BULLET_L_ST_SY;
        break;
    }
    
    this->sh = FISH_BULLET_SH;
    this->sw = FISH_BULLET_SW;
    
    this->fLpSx_ = FISH_BULLET_F_LP_SX;
    this->fLpSy_ = FISH_BULLET_F_LP_SY;
    this->fRpSx_ = FISH_BULLET_F_RP_SX;
    this->fRpSy_ = FISH_BULLET_F_RP_SY;
    this->bStSx_ = FISH_BULLET_B_ST_SX;
    this->bStSy_ = FISH_BULLET_B_ST_SY;
    this->bRpSx_ = FISH_BULLET_B_RP_SX;
    this->bRpSy_ = FISH_BULLET_B_RP_SY;
    this->bLpSx_ = FISH_BULLET_B_LP_SX;
    this->bLpSy_ = FISH_BULLET_B_LP_SY;
    this->lStSx_ = FISH_BULLET_L_ST_SX;
    this->lStSy_ = FISH_BULLET_L_ST_SY;
    this->lRpSx_ = FISH_BULLET_L_RP_SX;
    this->lRpSy_ = FISH_BULLET_L_RP_SY;
    this->lLpSx_ = FISH_BULLET_L_Lp_SX;
    this->lLpSy_ = FISH_BULLET_L_LP_SY;
    this->rStSx_ = FISH_BULLET_R_ST_SX;
    this->rStSy_ = FISH_BULLET_R_ST_SY;
    this->rRpSx_ = FISH_BULLET_R_RP_SX;
    this->rRpSy_ = FISH_BULLET_R_RP_SY;
    this->rLpSx_ = FISH_BULLET_R_LP_SX;
    this->rLpSy_ = FISH_BULLET_R_LP_SY;    
    this->dS1Sx_ = FISH_BULLET_D_S1_SX;
    this->dS1Sy_ = FISH_BULLET_D_S1_SY;
    this->dS2Sx_ = FISH_BULLET_D_S2_SX;
    this->dS2Sy_ = FISH_BULLET_D_S2_SY;
    this->dS3Sx_ = FISH_BULLET_D_S3_SX;
    this->dS3Sy_ = FISH_BULLET_D_S3_SY;
    Movable::SetMovements();
    this->DefineBlockPosition(row, column);  
    this->visitor = new FishBulletVisitor(this);   
    Stage::visitorlist.push_back(this->visitor);      
    
} 

void FishBullet::Accept(Visitor *visitor) const {
    visitor->VisitMob(this);
}

FishBulletVisitor::FishBulletVisitor(FishBullet * fishBullet){
    this->fishBullet = fishBullet;
}

void FishBulletVisitor::VisitWall(const Wall *element) const{        
    
    this->fishBullet->blockDown  |= this->fishBullet->BlockRow(element->component->row - 1, element->component->column );//blockleft
    this->fishBullet->blockUp    |= this->fishBullet->BlockRow(element->component->row + 1, element->component->column );//blockright
    this->fishBullet->blockRight |= this->fishBullet->BlockColumn(element->component->column - 1, element->component->row);//blockdown
    this->fishBullet->blockLeft  |= this->fishBullet->BlockColumn(element->component->column + 1, element->component->row);//blockup  

}

void FishBulletVisitor::VisitMob(const Mob *element) const{

}

void FishBulletVisitor::VisitBomb(const Bomb * element) const {
    
    this->fishBullet->blockDown  |= this->fishBullet->BlockRow(element->row - 1, element->column );//blockleft
    this->fishBullet->blockUp    |= this->fishBullet->BlockRow(element->row + 1, element->column );//blockright
    this->fishBullet->blockRight |= this->fishBullet->BlockColumn(element->column - 1, element->row);//blockdown
    this->fishBullet->blockLeft  |= this->fishBullet->BlockColumn(element->column + 1, element->row);//blockup      
}

  
FishBullet::~FishBullet(){
    
    delete this->movementStateMachine;        
    Visitor::RemoveVisitor( Stage::visitorlist, (Visitor *)this->visitor);    
    
}

void FishBullet::Colide() {

}

int FishBullet::GetEvent(int direction){
    
    switch (direction)
    {
        case UP:
            if(this->blockUp) { this->removed = true; return IDDLE;}
            break;            
        case DOWN:
            if(this->blockDown) { this->removed = true; return IDDLE;}
            break;      
        case LEFT:
            if(this->blockLeft) { this->removed = true; return IDDLE;}
            break;
        case RIGHT:
            if(this->blockRight) { this->removed = true; return IDDLE;}
            break;
    }

    return direction;

}

void FishBullet::Move() {
        
    int event = GetEvent(this->direction);                    
    movementStateMachine->Request(event);
           
}

void FishBullet::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}