#ifndef __StageSelector_H_
#define __StageSelector_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdlib> 
#include <ctime>
#include "../Assets/assets.h"
#include "../Engine/Component.h"
#include "../Components/Butterfly.h"
#include "../Components/GuardDog.h"
#include "../Components/JellyGirl.h"
#include "../Components/Octopus.h"
#include "../Components/ShotterPenguin.h"
#include "../Components/CaptainPenguin.h"
#include "../Components/FishBullet.h"

#define MAXROWNUMBER          8
#define MAXCOLUMNNUMBER       10

using namespace std;

typedef struct {
  int index;
  int row;
  int column;
} ComponentIndex;

class StageSelector{  
  
 public:
   int staticComponent, destructableWall;
   static StageSelector * StageFactory(int StageIndex);   
   static Component * ComponentFactory(int componentIndex, int column, int row, int consumable); 
   static vector<ComponentIndex> GetRandomComponents(list<Component*>& componentList, int noOfSpawnedComponents, bool (*forbidenSpots)(int, int));
   static bool  ValidateRandomNumber(vector<ComponentIndex>& randomList, int randomNumber);
   static void  BuildStaticComponents( list<Component*>& componentList, bool (*checkSpots)(int, int), int staticComponent );
   virtual void GetStageBitmap(ALLEGRO_BITMAP ** bitmap) = 0; 
   virtual void LoadStaticComponents( list<Component*>& componentList ) const = 0;
   virtual void LoadMobs( list<Component*>& componentList ) const = 0;
   virtual void LoadDestructableComponents( list<Component*>& componentList ) const = 0;
   virtual void LoadPlayerOne( 
     list<Component*>& componentList,
     int life,
     int bombStrength,
     int speed,
     int nOBombs
   ) const = 0;   
  
};

#endif