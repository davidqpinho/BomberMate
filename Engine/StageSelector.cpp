#include "StageSelector.h"
#include "../Stages/FieldStage.h"
#include "../Scenes/Stage.h"

StageSelector * StageSelector::StageFactory(int StageIndex){
       
     switch (StageIndex){
             case FIELDSTAGE:                 
             return new FieldStage();     
     }
     
     return NULL;
       
}; 


void  StageSelector::BuildStaticComponents( list<Component*>& componentList, bool (*checkSpots)(int, int), int staticComponent ){
        for(int row = 0; row < MAXROWNUMBER; row++){ 
        for(int column = 0; column < MAXCOLUMNNUMBER; column++){ 
            if( row == 0 || row == MAXROWNUMBER-1){                
                componentList.push_back(StageSelector::ComponentFactory(staticComponent,column,row, -1));
            }else if( (column == 0 || column == MAXCOLUMNNUMBER - 1 ) && (row > 0 && row < MAXROWNUMBER-1)){
                componentList.push_back(StageSelector::ComponentFactory(staticComponent,column,row, -1));
            }else if( checkSpots(column, row) && (row > 0 && row < MAXROWNUMBER-1) && (column > 0 && column < MAXCOLUMNNUMBER-1)){
                componentList.push_back(StageSelector::ComponentFactory(staticComponent,column,row, -1));
            }
        }
        
    }
}


Component * StageSelector::ComponentFactory(int componentIndex, int column, int row, int consumable){
       
     Component * component = NULL;
     
     switch (componentIndex){
        case BRICK:
        case ROCK:                 
        component = new StaticComponent(componentIndex, row, column);              
        break; 
        case BRICKWALL: 
        case ROCKWALL:
        component = new DestructableWall(componentIndex, row, column, consumable);                
        break;
        case GUARDDOG:
        component = new GuardDog(row, column);
        break;
        case BUTTERFLY:
        component = new Butterfly(row, column);
        break;
        case JELLYGIRL:
        component = new JellyGirl(row, column);
        break;
        case OCTOPUS:
        component = new Octopus(row, column);
        break;
        case SHOTTERPENGUIN:
        component = new ShotterPenguin(row, column);
        break;
        case CAPTAINPENGUIN:
        component = new CaptainPenguin(row, column);
        break;
     }
     return component; 
}

vector<ComponentIndex> StageSelector::GetRandomComponents(list<Component*>& componentList, int noOfSpawnedComponents, bool (*forbidenSpots)(int, int)){
        
     vector<ComponentIndex> allList, ramdomList; 
     int listIndex = 0;   
     int randomNumber; 

     //Add All positions available
     for(int row = 1; row < MAXROWNUMBER - 1; row++){
        for(int column = 1; column< MAXCOLUMNNUMBER - 1; column ++){
            if(!forbidenSpots( column, row)){
                allList.push_back({.row = row, .column = column});
            }           
        }
     }

  
     for (list<Component*>::iterator componentListIt = componentList.begin(); componentListIt != componentList.end(); ++componentListIt){
        //printf("FROM SCENE Component: %d, %d\n", (*componentListIt)->row, (*componentListIt)->column);
        for (vector<ComponentIndex>::iterator allListIt = allList.begin(); allListIt != allList.end(); ++allListIt){
            if((*componentListIt)->row == allListIt->row && (*componentListIt)->column == allListIt->column){
                allList.erase(allListIt);
                break;
            }
        }
     }
     
     //Index all the remaining position
     for(vector<ComponentIndex>::iterator allListIt = allList.begin(); allListIt != allList.end(); ++allListIt){
        listIndex++;
        allListIt->index = listIndex;
     }
     //collect the randomic position
     while( noOfSpawnedComponents > 0 ){
                     
        do{               
        randomNumber = rand() % listIndex + 1;   
        }while(!StageSelector::ValidateRandomNumber(ramdomList, randomNumber));
        
        for(vector<ComponentIndex>::iterator allListIt = allList.begin(); allListIt != allList.end(); ++allListIt){
                if(allListIt->index == randomNumber){
                ramdomList.push_back((*allListIt));
                }
        }    
        
        --noOfSpawnedComponents;
     }

     /*for(vector<ComponentIndex>::iterator it = ramdomList.begin(); it!= ramdomList.end(); it++){
             printf("component row:%d column:%d \n", it->row, it->column);
     }*/
     
     return ramdomList;

}

bool StageSelector::ValidateRandomNumber(vector<ComponentIndex>& randomList, int randomNumber){
        
     for(vector<ComponentIndex>::iterator radomListIt = randomList.begin();radomListIt != randomList.end(); ++ radomListIt){            
             if(radomListIt->index == randomNumber){
                     return false;   
             }    
     }
     
     return true;

}