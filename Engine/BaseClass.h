#ifndef __BASE_H_
#define __BASE_H_

#include "Component.h"

class Component;

class Wall {
    public:
    
        Component * component;

        bool hitByBomb = false;
        
        void SetHitByBomb(){
            this->hitByBomb = true;
        };   

        Wall( Component * component);
        virtual ~Wall(){};
};

class Mob {
    public:
    
        Component * component;
        
        bool hitByBomb = false;
        Mob(Component * component);
        virtual ~Mob(){};
}; 

#endif