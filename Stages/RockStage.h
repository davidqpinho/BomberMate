#ifndef __ROCKSTAGE_H_
#define __ROCKSTAGE_H_

#include <list>
#include <vector>
#include "../Engine/StageSelector.h"
#include "../Assets/assets.h"
#include "../Components/StaticComponent.h"
#include "../Components/DestructableWall.h"
#include "../Components/PlayerOne.h"
#include "../Components/GuardDog.h"
#include "../Components/ConsumableItem.h"

using namespace std;
class RockStage : public StageSelector  {
    
    private:
        static bool CheckStaticSpot(int column, int row);
        static bool CheckForForbidemSpots(int column, int row);      
    public:        
        RockStage();
        void GetStageBitmap(ALLEGRO_BITMAP ** bitmap) override;
        void LoadStaticComponents( list<Component*>& componentList ) const override;
        void LoadMobs( list<Component*>& componentList ) const override;
        void LoadDestructableComponents( list<Component*>& componentList ) const override;
        void LoadPlayerOne( list<Component*>& componentList ) const override;
 
};

#endif