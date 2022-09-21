#ifndef __GAME_H
#define __GAME_H

#include <string>
#include <stack>
#include <memory>

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

  void Push(State *state);

private:
  Game(std::string &title, int width, int height);
  static Game *instance;
  SDL_Window *window;
  SDL_Renderer *renderer;

  int frameStart;
  float dt;
  float GetDeltaTime();

  State *storedState;
  std::stack<std::unique_ptr<State>> stateStack;
};

#endif // __GAME_H
