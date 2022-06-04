#include "ConsumableItem.h"

ConsumableItem::ConsumableItem(int ConsumableItem, int row, int column){
    
   this->ItemType = ConsumableItem;
   Stage::GetSheet(this, 1);  
   this->zpos = 0;
   switch(ConsumableItem){
       case LIFE:
        this->sx = LIFE_SX;
        this->sy = LIFE_SY;        
        this->sh = LIFE_SH;
        this->sw = LIFE_SW;
        break;
       case STRG:
        this->sx = STRG_SX;
        this->sy = STRG_SY;        
        this->sh = STRG_SH;
        this->sw = STRG_SW;
        break;
       case SPD:
        this->sx = SPD_SX;
        this->sy = SPD_SY;        
        this->sh = SPD_SH;
        this->sw = SPD_SW;
        break;
       case NOBS:
        this->sx = NOBS_SX;
        this->sy = NOBS_SY;        
        this->sh = NOBS_SH;
        this->sw = NOBS_SW;
        break;
   } 

   this->DefineBlockPosition(row, column);       
   this->visitor = new ConsumableItemVisitor(this);
   Stage::visitorlist.push_back(this->visitor); 
} 
  
ConsumableItem::~ConsumableItem(){
    Visitor::RemoveVisitor( Stage::visitorlist, (Visitor *)this->visitor);
}

void ConsumableItem::Colide(){}

void ConsumableItem::Move() {}

void ConsumableItem::SetDestructionState(int step){}

void ConsumableItem::Accept(Visitor *visitor) const {
    visitor->VisitConsumableItem(this);
}

void ConsumableItem::Draw() {
    al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
}

ConsumableItemVisitor::ConsumableItemVisitor(ConsumableItem * consumableItem){
    this->consumableItem = consumableItem;
}

void ConsumableItemVisitor::VisitPlayerOne(const PlayerOne *player) const{
    
    PlayerOne * playerModifier;
    playerModifier = (PlayerOne*) player;

    if( this->consumableItem->removed == false       &&
        this->consumableItem->row == player->row     && 
        this->consumableItem->column == player->column){
    
           switch (this->consumableItem->ItemType)
           {
           case LIFE:
               playerModifier->AddLife();
               break;
            case NOBS:
               playerModifier->AddNoOfBombs();
               break;
            case SPD:
               playerModifier->AddSpeed();
               break;
            case STRG:
               playerModifier->AddBombStrenhth();
               break;
           default:
               break;
           }
           this->consumableItem->removed = true;
    }

}