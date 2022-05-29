#include "PlayerObserver.h"

void PlayerObserver::SetStatus(int life, int bombStrength, int speed, int column, int line, int nOBombs){
    this->event = line + (column << 4) + (speed << 8) + ( bombStrength << 16 ) + (life << 20) + (nOBombs << 24);
    this->subject_.Notify(this->event);
}

int  PlayerObserver::GetNOBombs(){    
    return (this->event & 251658240) >> 24;
}

int  PlayerObserver::GetLife(){    
    return (this->event & 15728640) >> 20;
}

int  PlayerObserver::GetBombStrength(){
    return (this->event & 983040) >> 16;
}

int  PlayerObserver::GetSpeed(){    
    int realSpeed = (this->event & 65280) >> 8;
    return (realSpeed - 8)/2;
}

int  PlayerObserver::GetLine(){
    return this->event & 15;
}

int  PlayerObserver::GetColumn(){
    return (this->event & 240) >> 4;
}

PlayerObserver::PlayerObserver(PlayerSubject &subject) : subject_(subject) {

    this->subject_.Attach(this);

}   

void PlayerObserver::Update(int event) {

    this->event = event;

}

int PlayerObserver::ReadEvent(){
    
    return this->event;   

}

int PlayerObserver::GetEvent(){

    int ret = this->event;    
    return ret;

}

void PlayerObserver::RemoveMeFromTheList() {

    subject_.Detach(this);

}   
  
void PlayerSubject::Attach(IPlayerObserver *observer) {

    list_observer_.push_back(observer);

}

void PlayerSubject::Detach(IPlayerObserver *observer) {

    list_observer_.remove(observer);

}

void PlayerSubject::Notify(int event) {

    list<IPlayerObserver *>::iterator iterator = list_observer_.begin();

    while (iterator != list_observer_.end()) {
        (*iterator)->Update(event);
        ++iterator;
    }

}

void PlayerSubject::CreateEvent(int event) { 

    Notify(event);

}   

PlayerSubject::~PlayerSubject(){
    for(list<IPlayerObserver *>::iterator it = this->list_observer_.begin(); 
        it!=this->list_observer_.end(); 
        ++it){
        delete * it;
    }
}
