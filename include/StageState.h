#ifndef __STAGE_STATE_H
#define __STAGE_STATE_H

#include <memory>
#include <string>
#include <vector>

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"
#include "TileSet.h"

class StageState : public State {
public:
  StageState();
  ~StageState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void Start();
  void Pause();
  void Resume();
private:
  TileSet *tileSet;
  Music backgroundMusic;
};

#endif // __STAGE_STATE_H
