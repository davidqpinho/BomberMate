#include "DestructableWall.h"

DestructableWall::DestructableWall(int DestructableWall, int row, int column, int consumable): Wall(this){
    
   this->WallType = DestructableWall;
   this->consumable = consumable;
   
   switch(DestructableWall){
       case BRICKWALL:
        this->sx = BRICKWALL_SX;
        this->sy = BRICKWALL_SY;        
        this->sh = BRICKWALL_SH;
        this->sw = BRICKWALL_SW;
        Stage::GetSheet(this, 2);
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
    switch (this->WallType)
    {
        case BRICKWALL:

            switch (step)
            {
                case 1:
                    this->sx = BCKW_D1_SX;
                    this->sy = BCKW_D1_SY;        
                    break; 
                case 2:
                    this->sx = BCKW_D2_SX;
                    this->sy = BCKW_D2_SY;        
                    break;   
                case 3:
                    this->sx = BCKW_D3_SX;
                    this->sy = BCKW_D3_SY;        
                    break;     
            }

            break;
    }
    
}

void DestructableWall::Accept(Visitor *visitor) const {
    visitor->VisitWall(this);
}

void DestructableWall::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}