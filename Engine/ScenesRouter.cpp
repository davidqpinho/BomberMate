#include "ScenesRouter.h"

void Scene::set_scene(SceneRouter *scene) {
    this->scene_ = scene;
}

SceneRouter::SceneRouter(Scene *state) : scene_(nullptr) {
    this->TransitionTo(state);
}

SceneRouter::~SceneRouter() {
    delete scene_;
}

void SceneRouter::TransitionTo(Scene *state) {    
    if (this->scene_ != nullptr)
        delete this->scene_;
    this->scene_ = state;
    this->scene_->set_scene(this);
}

void SceneRouter::Request1() {
    this->scene_->Handle();
}

void SceneRouter::Request2() {
    this->scene_->Handle();
}

void SceneRouter::ProcessScene(){    	
	
    al_clear_to_color(al_map_rgba_f(0, 0, 0, 1));	
    this->scene_->Run();    
    al_flip_display();
    
}

int SceneRouter::ProcessEvent(ALLEGRO_EVENT * event, ALLEGRO_EVENT_QUEUE ** queue){

    int ret = true;

    ret = this->scene_->ProcessEvent(&event);    

    return ret;

}

