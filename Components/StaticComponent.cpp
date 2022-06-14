#include "StaticComponent.h"


StaticComponent::StaticComponent(int StaticComponent, int row, int column): Wall(this){
   
   Stage::GetSheet(this, 2);
   switch(StaticComponent){
       case BRICK:
        this->sx = BRICK_SX;
        this->sy = BRICK_SY;
        this->sh = BRICK_SH;
        this->sw = BRICK_SW;
        break;
       case ROCK:
        this->sx = ROCK_SX;
        this->sy = ROCK_SY;
        this->sh = ROCK_SH;
        this->sw = ROCK_SW;        
       break;
   }

   this->DefineBlockPosition(row, column);
    
} 

void StaticComponent::Accept(Visitor *visitor) const {
    visitor->VisitWall(this);
}
  
StaticComponent::~StaticComponent(){
}

void StaticComponent::Colide() {

}
void StaticComponent::Move() {

}

void StaticComponent::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}