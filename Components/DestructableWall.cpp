#include "DestructableWall.h"

DestructableWall::DestructableWall(int DestructableWall, int row, int column, int consumable): Wall(this){
    
   this->WallType = DestructableWall;
   this->consumable = consumable;
   
   Stage::GetSheet(this, 2);
   
   switch(DestructableWall){
       case BRICKWALL:
        this->sx     = BRICKWALL_SX;
        this->sy     = BRICKWALL_SY;        
        this->sh     = BRICKWALL_SH;
        this->sw     = BRICKWALL_SW;
        this->DS1_SX = BCKW_D1_SX;
        this->DS1_SY = BCKW_D1_SY;
        this->DS2_SX = BCKW_D2_SX;
        this->DS2_SY = BCKW_D2_SY;
        this->DS3_SX = BCKW_D3_SX;
        this->DS3_SY = BCKW_D3_SY;
        break;
       case ROCKWALL:
        this->sx     = ROCKWALL_SX;
        this->sy     = ROCKWALL_SY;        
        this->sh     = ROCKWALL_SH;
        this->sw     = ROCKWALL_SW;
        this->DS1_SX = ROCKWALL_D1_SX;
        this->DS1_SY = ROCKWALL_D1_SY;
        this->DS2_SX = ROCKWALL_D2_SX;
        this->DS2_SY = ROCKWALL_D2_SY;
        this->DS3_SX = ROCKWALL_D3_SX;
        this->DS3_SY = ROCKWALL_D3_SY;
       break;
   } 

   this->DefineBlockPosition(row, column);       
    
} 
  
DestructableWall::~DestructableWall(){
    
}

void DestructableWall::Colide() {

}

void DestructableWall::Move() {
    
    if(((Wall*)this)->hitByBomb){

        if(this->destructionCounter < DEST_STEP3)this->destructionCounter++;

        if(this->destructionCounter < DEST_STEP1){ 
            this->SetDestructionState(1);  
        }else if(this->destructionCounter < DEST_STEP2){
            this->SetDestructionState(2);  
        }else if(this->destructionCounter < DEST_STEP3){
            this->SetDestructionState(3);  
        }else{
            this->removed = true;
        }

    }
}

void DestructableWall::SetDestructionState(int step){
            
    switch (step)
    {
        case 1:
            this->sx = this->DS1_SX;
            this->sy = this->DS1_SY;        
            break; 
        case 2:
            this->sx = this->DS2_SX;
            this->sy = this->DS2_SY;        
            break;   
        case 3:
            this->sx = this->DS3_SX;
            this->sy = this->DS3_SY;        
            break;     
    }

         
}

void DestructableWall::Accept(Visitor *visitor) const {
    visitor->VisitWall(this);
}

void DestructableWall::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}