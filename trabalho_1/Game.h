#include <string>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

struct State {};

class Game {
public:
  void Run();
  SDL_Renderer* GetRenderer();
  State &GetState();
  Game &GetInstance();
  virtual ~Game();

private:
  Game(std::string &title, int width, int height);
  Game *instance;
  SDL_Window *window;
  SDL_Renderer *renderer;
  State *state;
};
