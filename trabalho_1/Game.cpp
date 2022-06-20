#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>

Game::Game(std::string &title, int width, int height) {
  // somente uma instância pode estar rodando
  if (instance != nullptr) {
    std::exit(1);
  }

  // TODO: verificar error do init
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

  Mix_Init(MIX_INIT_OGG);
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS,
                1024);

  Mix_AllocateChannels(8);

  SDL_Window *window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, 0);
  SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_SOFTWARE | SDL_RENDERER_ACCELERATED |
                         SDL_RENDERER_PRESENTVSYNC |
                         SDL_RENDERER_TARGETTEXTURE);

  state = new State();
}

Game::~Game() {
  // TODO: delete state?
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

State &Game::GetState() {
  return *state;
}

SDL_Renderer* Game::GetRenderer() {
  return renderer;
}

void Game::Run() {
  // TODO
}

Game &Game::GetInstance() {
  if (this->instance != nullptr) {
    return *instance;
  } else {
    instance = new Game("game", 320, 200);
    return *instance;
  }
}
