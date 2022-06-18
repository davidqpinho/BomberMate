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
  int stage,
  life,
  bombStrength,
  speed,
  nOBombs;

 public:
  StageTransition(int stage, int life, int bombStrength, int speed, int nOBombs);
  ~StageTransition();
  int Handle() override;
  void Run() override;
  int ProcessEvent(ALLEGRO_EVENT ** event) override;
};

#endif