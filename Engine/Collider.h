#ifndef __COLLIDER_H_
#define __COLLIDER_H_
    
    #include <vector>
    #include "BaseClass.h"

    using namespace std;

    class PlayerOne;
    class Wall;
    class Mob;    
    class Visitor;
    class Bomb;

    class VisitorComponent {
    public:
        virtual ~VisitorComponent() {}
        virtual void Accept(Visitor *visitor) const = 0;
    };
    
    class Visitor {
    
    public:
        virtual void VisitPlayerOne(const PlayerOne *player) const = 0;  
        virtual void VisitWall(const Wall *element) const = 0;  
        virtual void VisitMob(const Mob *element) const = 0; 
        virtual void VisitBomb(const Bomb *elemens) const = 0;   
        
        static void  RemoveVisitor(vector<Visitor *> &visitorList, Visitor * visitor){
        
            for(vector<Visitor *>::iterator it = visitorList.begin(); it!=visitorList.end();){
            
                if((*it) == (visitor)){
                    delete * it;  
                    it = visitorList.erase(it);
                }
                else {
                    ++it;
                }
            }
        }
    };
    

    

    
#endif