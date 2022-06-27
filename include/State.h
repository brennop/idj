#ifndef __STATE_H
#define __STATE_H

#include <string>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Sprite.h"
#include "Music.h"

class State {
public:
  State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
private:
  Sprite bg;
  Music music;
  bool quitRequested;
};

#endif // __STATE_H
