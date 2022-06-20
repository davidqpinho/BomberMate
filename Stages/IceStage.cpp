#include "IceStage.h"

IceStage::IceStage(){
    this->staticComponent = ICECUBE;
    this->destructableWall = SNOWMAN;
}

void IceStage::GetStageBitmap(ALLEGRO_BITMAP ** bitmap) {

    (*bitmap) = al_load_bitmap(IceStageImg); 

}

void IceStage::LoadStaticComponents( list<Component*>& componentList)  const {    
    StageSelector::BuildStaticComponents(componentList, CheckStaticSpot, this->staticComponent);    
}


bool IceStage::CheckStaticSpot(int column, int row) {

    if(column==2 && row == 2) return true;
    if(column==2 && row == 5) return true;
    if(column==7 && row == 2) return true;
    if(column==7 && row == 5) return true;
    if(column==1 && row == 3) return true;
    if(column==1 && row == 4) return true;
    if(column==8 && row == 3) return true;
    if(column==8 && row == 4) return true;
    if(column==4 && row == 2) return true;
    if(column==5 && row == 5) return true;
    return false;

}

void IceStage::LoadDestructableComponents( list<Component*>& componentList ) const {
     vector<ComponentIndex> ramdomComponents;
     componentList.push_back(StageSelector::ComponentFactory(this->destructableWall,6,6, -1));
     ramdomComponents = StageSelector::GetRandomComponents(componentList, 15, CheckForForbidemSpots);
     int counter = 0;
     
     for(vector<ComponentIndex>::iterator ramdomComponentsIt = ramdomComponents.begin(); ramdomComponentsIt != ramdomComponents.end(); ramdomComponentsIt ++, counter++){
         int consumable = -1;
         if(counter == 4)
            consumable = LIFE;
         if(counter == 8)
            consumable = STRG;
         if(counter == 12)
            consumable = SPD;
         if(counter == 14)
            consumable = DOOR;
         if(counter == 0)
            consumable = NOBS;

         componentList.push_back(StageSelector::ComponentFactory(this->destructableWall,ramdomComponentsIt->column,ramdomComponentsIt->row, consumable));
     }     
}

bool IceStage::CheckForForbidemSpots(int column, int row){
    //if(column==2 && row == 2) return true;
    if(column==4 && row == 4) return true;
    if(column==8 && row == 5) return true;
    if(column==8 && row == 6) return true;
    if(column==7 && row == 6) return true;
    if(column==6 && row == 6) return true;
    return false;   
}

void IceStage::LoadMobs( list<Component*>& componentList ) const {
    
    vector<ComponentIndex> ramdomComponents;
    int count = 0, mob;
    
    ramdomComponents = StageSelector::GetRandomComponents(componentList, 4, CheckForForbidemSpots);
    
    for(vector<ComponentIndex>::iterator ramdomComponentsIt = ramdomComponents.begin(); ramdomComponentsIt != ramdomComponents.end(); ramdomComponentsIt ++, count++){
    
        mob = count%2 == 0 ? SHOTTERPENGUIN: CAPTAINPENGUIN;
    
        componentList.push_back(
             StageSelector::ComponentFactory(mob,ramdomComponentsIt->column,ramdomComponentsIt->row, -1)
        );
     }
}

void IceStage::LoadPlayerOne( list<Component*>& componentList, int life, int bombStrength, int speed, int nOBombs ) const {
    
    Component * playerOne = new PlayerOne(6,8,life,bombStrength,speed,nOBombs);
    playerOne->sheet = &Stage::sheet1;
    if(!playerOne->sheet ) 
    {
       printf("Error loading Player Bitmap.");
       exit(1);
    }
    componentList.push_back(playerOne);
}


