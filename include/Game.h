#ifndef __GAME_H
#define __GAME_H

#include <string>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"

class Game {
public:
  void Run();
  SDL_Renderer *GetRenderer();
  State &GetState();
  static Game &GetInstance();
  virtual ~Game();

private:
  Game(std::string &title, int width, int height);
  static Game *instance;
  SDL_Window *window;
  SDL_Renderer *renderer;
  State *state;
};

#endif // __GAME_H
