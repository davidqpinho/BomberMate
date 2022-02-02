#ifndef __SCHENES_ROUTER_H_
#define __SCHENES_ROUTER_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class SceneRouter;

class Scene {
 
 protected:
  SceneRouter *scene_;

 public:
  virtual ~Scene() {}

  void set_scene(SceneRouter *scene);

  virtual void Run() = 0;
  virtual int  ProcessEvent(ALLEGRO_EVENT ** event) = 0;
  virtual int  Handle() = 0;
  
};

class SceneRouter {
  
 private:
  Scene *scene_;

 public:
  SceneRouter(Scene *state);
  ~SceneRouter() ;
  
  void TransitionTo(Scene *state);
  
  void Request1();
  void Request2();
  void ProcessScene();
  int  ProcessEvent(ALLEGRO_EVENT * event, ALLEGRO_EVENT_QUEUE ** queue);
  
};



#endif