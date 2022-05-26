#include "Bomb.h"

Bomb::Bomb(int row, int column){
    
    this->bombObserver = new BombObserver(* Stage::bombSubject);    
    this->sh = 80;
    this->sw = 100;
    this->bombCounter = 0;
    this->state = BURNING;
    this->strength = 2;
    this->blockUpLv = this->strength; 
    this->blockDownLv = this->strength;
    this->blockRightLv = this->strength;
    this->blockLeftLv = this->strength;

    this->upWall     = NULL;
    this->bottomWall = NULL;
    this->rigthWall  = NULL;
    this->leftWall   = NULL;
    Stage::GetSheet(this, 1);
    DefinePosition(this->sx, this->sy, SHSHEET, SWSHEET, XOFFSET, YOFFSET, this->bombCounter, 0);
    
    this->DefineBlockPosition(row, column);       
    this->visitor = new BombVisitor(this);
    Stage::visitorlist.push_back(this->visitor); 
} 
  
Bomb::~Bomb(){
   this->bombObserver->RemoveMeFromTheList();
   delete this->bombObserver; 
   Visitor::RemoveVisitor( Stage::visitorlist, (Visitor *)this->visitor);
}

void Bomb::Colide() {

}

void Bomb::Move() {
    if(this->explosionCounter >= EXPFINALSTEP){
        if(this->upWall != NULL) this->upWall->SetHitByBomb();
        if(this->leftWall != NULL) this->leftWall->SetHitByBomb();
        if(this->rigthWall != NULL) this->rigthWall->SetHitByBomb();
        if(this->bottomWall != NULL) this->bottomWall->SetHitByBomb();
    }
}

void Bomb::Accept(Visitor *visitor) const {
     visitor->VisitBomb(this);
}

void Bomb::Draw() {
    this->bombCounter ++;
    if(this->state == BURNING && this->bombCounter < BOMBCOUNTERMAX){
        DefinePosition(this->sx, this->sy, SHSHEET, SWSHEET, XOFFSET, YOFFSET, this->bombColumn, this->bombCounter/BOMBCOUNTERSTEP);       
    }else{       
        
        if (this->bombColumn == 5)
        {
            this->bombColumn = 6;
            this->bombCounter = 0;
        }else{
            this->state = EXPLODED;
        }
        
    }
    if(this->state == EXPLODED){
        this->DrawExplosion();
    }else{
        al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
    }
    /*
    if(this->state==VANISHED){
        al_draw_bitmap_region((*this->sheet), this->sx, this->sy, this->sw, this->sh, this->dx, this->dy, 0);
         this->DrawExplosionLevel(1);
    }*/
    
}

void Bomb::DrawExplosion(){ 
    
    if(++this->explosionCounter < EXPLOSIONEND){        
        
        if( this->explosionCounter < EXPLOSIONSTEP){
            DefinePosition(this->sx, this->sy, SHSHEET, SWSHEET, XOFFSET, YOFFSET, 4, 3);
            this->DrawExplodedPlace(this->row, this->column, this->sx, this->sy, this->sw, this->sh, 0, 0);
        } else if( this->explosionCounter < EXPLOSIONSTEP*2 ){
            DefinePosition(this->sx, this->sy, SHSHEET, SWSHEET, XOFFSET, YOFFSET, 4, 4);
            this->DrawExplodedPlace(this->row, this->column, this->sx, this->sy, this->sw, this->sh, 0, 0);
        } else  if( this->explosionCounter < EXPLOSIONSTEP){
            DefinePosition(this->sx, this->sy, SHSHEET, SWSHEET, XOFFSET, YOFFSET, 4, 5);
            this->DrawExplodedPlace(this->row, this->column, this->sx, this->sy, this->sw, this->sh, 0, 0);
        } else if( this->explosionCounter < EXPLOSIONSTEP*4){
            DefinePosition(this->sx, this->sy, SHSHEET, SWSHEET, XOFFSET, YOFFSET, 4, 6);
            this->DrawExplodedPlace(this->row, this->column, this->sx, this->sy, this->sw, this->sh, 0, 0);
        } else if( this->explosionCounter > EXPLOSIONSTEP*4){            
            this->DrawFinalStep();
        }

    }else{    
        this->bombObserver->RemoveMeFromTheList();        
        this->state = VANISHED;
        this->removed = true;
    }
}

void Bomb::DrawFinalStep(){
    
    DefinePosition(this->sx, this->sy, SHSHEET, SWSHEET, XOFFSET, YOFFSET, 4, 7);
    this->DrawExplodedPlace(this->row, this->column, this->sx, this->sy, this->sw, this->sh, 0, 0);
    this->rangeDefined = true;
    this->DrawExplosionLevel(1);    
}

void Bomb::DrawExplodedPlace(int row, int column, int sx, int sy, int sw, int sh, int fineX, int fineY){

    int dx, dy;
    vector<ExplodedPosition>::iterator it;
    
    /*for( it = this->explodedPlaces.begin(); it != this->explodedPlaces.end(); it++){
        if((*it).row == row && (*it).column == column) break;
    }

    if(it == this->explodedPlaces.end()){
        ExplodedPosition pressedButtom = {.row = row, .column = column};
        this->explodedPlaces.push_back(pressedButtom);
    }*/

    dy = (row * BLOCKHEIGHT) + ((BLOCKHEIGHT - this->sh)/2) + fineY;
    dx = (column * BLOCKWIDTH  + HEADERSIZE) + ((BLOCKWIDTH - this->sw)/2)+fineX; 

    al_draw_bitmap_region((*this->sheet), sx, sy, sw, sh, dx, dy, 0);
}

void Bomb::DrawExplosionLevel(int Level){
    
    float sxUp, syUp, sxDown, syDown, sxLeft, syLeft, sxRight, syRight;

    if(this->strength > 1){        
        
        this->DrawNotBlocked(3,6,8,8,this->row  - 1, this->column,sxUp,syUp,this->blockUpLv, 1);
        this->DrawNotBlocked(1,3,0,-8,this->row  + 1, this->column,sxDown,syDown,this->blockDownLv, 1);        
        this->DrawNotBlocked(2,1,0,0,this->row, this->column - 1,sxLeft,syLeft,this->blockLeftLv, 1);
        this->DrawNotBlocked(2,7,0,5,this->row, this->column + 1,sxRight,syRight,this->blockRightLv, 1);
        
    
    }if(this->strength > 2){   

        this->DrawNotBlocked(3,7,4,16,this->row  - 2, this->column,sxUp,syUp,this->blockUpLv, 2);
        this->DrawNotBlocked(1,4,4,-17,this->row  + 2, this->column,sxDown,syDown,this->blockDownLv, 2);        
        this->DrawNotBlocked(2,2,0,0,this->row, this->column - 2,sxLeft,syLeft,this->blockLeftLv, 2);
        this->DrawNotBlocked(3,2,0,3,this->row, this->column + 2,sxRight,syRight,this->blockRightLv, 2);

    } 

    this->DrawExplosionEnd( sxUp, syUp, sxDown, syDown, sxLeft, syLeft, sxRight, syRight );       


}

void Bomb::DrawExplosionEnd(float sxUp, float syUp, float sxDown, float syDown, float sxLeft, float syLeft, float sxRight, float syRight){
    
    if(this->strength == 1){       
        
        this->DrawNotBlocked(4,0,8,8,this->row  - this->strength, this->column,sxUp,syUp,this->blockUpLv, 1);
        this->DrawNotBlocked(1,5,0,-8,this->row  + this->strength, this->column,sxDown,syDown,this->blockDownLv, 1);        
        this->DrawNotBlocked(2,3,0,0,this->row, this->column - this->strength,sxLeft,syLeft,this->blockLeftLv, 1);
        this->DrawNotBlocked(3,1,0,5,this->row, this->column + this->strength,sxRight,syRight,this->blockRightLv, 1);

    }else if(this->strength == 2){

        this->DrawNotBlocked(3,5,4,16,this->row  - this->strength, this->column,sxUp,syUp,this->blockUpLv, 2);
        this->DrawNotBlocked(1,7,4,-17,this->row  + this->strength, this->column,sxDown,syDown,this->blockDownLv,2);        
        this->DrawNotBlocked(2,5,3,3,this->row, this->column - this->strength,sxLeft,syLeft,this->blockLeftLv,2);
        this->DrawNotBlocked(3,3,0,3,this->row, this->column + this->strength,sxRight,syRight,this->blockRightLv,2);

    }else if(this->strength == 3){
 
        this->DrawNotBlocked(4,2,4,24,this->row  - this->strength, this->column,sxUp,syUp,this->blockUpLv,3);
        this->DrawNotBlocked(2,0,4,-26,this->row  + this->strength, this->column,sxDown,syDown,this->blockDownLv,3);        
        this->DrawNotBlocked(2,6,0,0,this->row, this->column - this->strength,sxLeft,syLeft,this->blockLeftLv,3);
        this->DrawNotBlocked(3,4,0,3,this->row, this->column + this->strength,sxRight,syRight,this->blockRightLv,3);

    }
}

void Bomb::DrawNotBlocked(int shrow, int shcolumn, int fineX, int fineY, int row_, int column_, float sx_, float sy_, int blockedLv, int ExplosionLv){
    if( ExplosionLv <= blockedLv){
        DefinePosition(sx_, sy_, SHSHEET, SWSHEET, XOFFSET, YOFFSET, shrow, shcolumn);
        this->DrawExplodedPlace(row_, column_, sx_, sy_, this->sw, this->sh, fineX, fineY);               
    }
}

BombVisitor::BombVisitor(Bomb * bomb){
    this->bomb = bomb;
}

bool Bomb::CheckIfHit(int row, int column) const {
       
    if((this->rangeDefined ) && 
    ((column == this->column && row <= (this->row + this->blockDownLv) && row >= (this->row - this->blockUpLv)) ||
    (row == this->row && column <= (this->column + this->blockRightLv) && column >= (this->column - this->blockLeftLv)))
    ){
       return true;
    }
       
    return false;
}

void BombVisitor::VisitWall(const Wall *element) const{    
    
    if(this->bomb->explosionCounter >= EXPFINALSTEP){
        
        if(this->SetBlockLevel(this->bomb->column, element->component->column, this->bomb->row, element->component->row, &this->bomb->blockUpLv)){
            this->bomb->upWall = (Wall *) element;
        }
        
        if(this->SetBlockLevel(this->bomb->column, element->component->column, element->component->row, this->bomb->row , &this->bomb->blockDownLv)){
            this->bomb->bottomWall = (Wall *) element;
        }        

        if(this->SetBlockLevel(this->bomb->row, element->component->row, this->bomb->column, element->component->column , &this->bomb->blockLeftLv)){
            this->bomb->leftWall = (Wall *) element;
        }
      
        if(this->SetBlockLevel(this->bomb->row, element->component->row, element->component->column, this->bomb->column , &this->bomb->blockRightLv)){
            this->bomb->rigthWall = (Wall *) element;
        }        
       //printf("Up:%d Down:%d Left:%d Right:%d\n", this->bomb->blockUpLv, this->bomb->blockDownLv,this->bomb->blockLeftLv, this->bomb->blockRightLv);
    } 

}

bool BombVisitor::SetBlockLevel(int bombEqualDirection, int wallEqualDirection, int higherLevel, int lowerLevel, int * level) const{
    
    int blocksBetween;
    
    if((!this->bomb->rangeDefined)  && bombEqualDirection == wallEqualDirection && higherLevel > lowerLevel){
        blocksBetween = abs(higherLevel - lowerLevel) - 1;
        if(blocksBetween <= this->bomb->strength && blocksBetween < (*level) ){
            //printf("equal: %d\n", bombEqualDirection);
            (*level) = blocksBetween;
            return true;
        }            
    }

    return false;
}

