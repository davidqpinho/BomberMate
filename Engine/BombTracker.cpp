#include "BombTracker.h"

BombObserver::BombObserver(BombSubject &subject) : subject_(subject) {

    this->subject_.Attach(this);

}   

void BombObserver::Update(int event) {

    this->event = event;

}

int BombObserver::ReadEvent(){
    
    return this->event;   

}

int BombObserver::GetEvent(){

    int ret = this->event;    
    return ret;

}

void BombObserver::RemoveMeFromTheList() {
    
    subject_.Detach(this);

}   

void BombSubject::AddBombSet()
{
        this->bombsSet ++ ;
}

void BombSubject::RemoveBombSet()
{
        this->bombsSet -- ;
}
  
void BombSubject::Attach(IBombObserver *observer) {

    list_observer_.push_back(observer);

}

void BombSubject::Detach(IBombObserver *observer) {
    
    
    if(this->bombsSet > 0)
        this->RemoveBombSet();
    
    
    list_observer_.remove(observer);
}

void BombSubject::Notify(int event) {

    list<IBombObserver *>::iterator iterator = list_observer_.begin();

    while (iterator != list_observer_.end()) {
        (*iterator)->Update(event);
        ++iterator;
    }

}

void BombSubject::CreateEvent(int event) { 

    Notify(event);

}   

int BombSubject::CanSpawnBombs(int playerBombs){
    if( this->bombTimer == 0 && playerBombs > this->bombsSet){
        this->bombTimer = 20;
        this->bombsSet++;
     return 1;
    }
    return 0;
}

void BombSubject::UpdateTimer(){
    if(this->bombTimer > 0)
        this->bombTimer --;
}

BombSubject::~BombSubject(){
    for(list<IBombObserver *>::iterator it = this->list_observer_.begin(); 
        it!=this->list_observer_.end(); 
        ++it){
        delete * it;
    }
}
