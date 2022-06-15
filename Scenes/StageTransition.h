#ifndef __STAGE_TRANSITION_H_
#define __STAGE_TRANSITION_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../Engine/ScenesRouter.h"
#include "../Engine/ScenesRouter.h"
#include "../Assets/assets.h"
#include "Stage.h"


class StageTransition : public Scene {
 private:
  int stage;

 public:
  StageTransition(int stage);
  ~StageTransition();
  int Handle() override;
  void Run() override;
  int ProcessEvent(ALLEGRO_EVENT ** event) override;
};

#endif