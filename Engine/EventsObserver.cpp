#include "EventsObserver.h"

Observer::Observer(Subject &subject) : subject_(subject) {

    this->subject_.Attach(this);

}   

void Observer::Update(int event) {

    this->event = event;

}

int Observer::ReadEvent(){
    
    return this->event;   

}

int Observer::GetEvent(){

    int ret = this->event;
    this->event = -1;
    return ret;

}

void Observer::RemoveMeFromTheList() {

    subject_.Detach(this);

}   
  
void Subject::Attach(IObserver *observer) {

    list_observer_.push_back(observer);

}

void Subject::Detach(IObserver *observer) {

    list_observer_.remove(observer);

}

void Subject::Notify(int event) {

    list<IObserver *>::iterator iterator = list_observer_.begin();

    while (iterator != list_observer_.end()) {
        (*iterator)->Update(event);
        ++iterator;
    }

}

void Subject::CreateEvent(int event) { 

    Notify(event);

}   