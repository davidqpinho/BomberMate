#include "FieldStage.h"

FieldStage::FieldStage(int staticComponent, int destructableWall){
    this->staticComponent = staticComponent;
    this->destructableWall = destructableWall;
}

void FieldStage::GetStageBitmap(ALLEGRO_BITMAP ** bitmap) {

    (*bitmap) = al_load_bitmap(FieldStageImg); 

}

void FieldStage::LoadStaticComponents( list<Component*>& componentList )  const {    
    StageSelector::BuildStaticComponents(componentList, CheckStaticSpot, this->staticComponent);    
}


bool FieldStage::CheckStaticSpot(int column, int row) {

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

void FieldStage::LoadDestructableComponents( list<Component*>& componentList ) const {

     vector<ComponentIndex> ramdomComponents;

     componentList.push_back(StageSelector::ComponentFactory(BRICKWALL,6,6));
     ramdomComponents = StageSelector::GetRandomComponents(componentList, 15, CheckForForbidemSpots);

     for(vector<ComponentIndex>::iterator ramdomComponentsIt = ramdomComponents.begin(); ramdomComponentsIt != ramdomComponents.end(); ramdomComponentsIt ++){
         componentList.push_back(StageSelector::ComponentFactory(BRICKWALL,ramdomComponentsIt->column,ramdomComponentsIt->row));
     }
     
}

bool FieldStage::CheckForForbidemSpots(int column, int row){
    //if(column==2 && row == 2) return true;
    if(column==4 && row == 4) return true;
    if(column==8 && row == 5) return true;
    if(column==8 && row == 6) return true;
    if(column==7 && row == 6) return true;
    if(column==6 && row == 6) return true;
    return false;   
}

void FieldStage::LoadMobs( list<Component*>& componentList ) const {
    //Component * mob = new GuardDog(2,8);
    // if(!mob->sheet ) 
    // {
    //    printf("Error loading Player Bitmap.");
    //    exit(1);
    // }
    vector<ComponentIndex> ramdomComponents;
    ramdomComponents = StageSelector::GetRandomComponents(componentList, 4, CheckForForbidemSpots);
    for(vector<ComponentIndex>::iterator ramdomComponentsIt = ramdomComponents.begin(); ramdomComponentsIt != ramdomComponents.end(); ramdomComponentsIt ++){
         componentList.push_back(new GuardDog(ramdomComponentsIt->row,ramdomComponentsIt->column));
     }
}

void FieldStage::LoadPlayerOne( list<Component*>& componentList ) const {
    
    Component * playerOne = new PlayerOne(6,8);
    playerOne->sheet = &Stage::sheet1;
    if(!playerOne->sheet ) 
    {
       printf("Error loading Player Bitmap.");
       exit(1);
    }
    componentList.push_back(playerOne);
}


