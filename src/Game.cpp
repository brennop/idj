#include "Game.h"
#include "InputManager.h"
#include "Resources.h"
#include "common.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <string>

Game *Game::instance = nullptr;

Game::Game(std::string &title, int width, int height) {
  // somente uma instância pode estar rodando
  if (instance != nullptr) {
    std::exit(1);
  }

  instance = this;

  // TODO: verificar error do init
  int init = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
  CHECK_ERROR_INT(init);

  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

  Mix_Init(MIX_INIT_OGG);
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS,
                1024);

  Mix_AllocateChannels(8);

  SDL_Window *window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, 0);

  CHECK_ERROR(window);

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE
      // | SDL_RENDERER_ACCELERATED
      // | SDL_RENDERER_PRESENTVSYNC
  );

  CHECK_ERROR(renderer);

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

State &Game::GetState() { return *state; }

SDL_Renderer *Game::GetRenderer() { return renderer; }

void Game::Run() {
  state->Start();
  while (!state->QuitRequested()) {
    int newFrameTime = SDL_GetTicks();

    dt = (newFrameTime - frameStart) / 1000.0f;
    frameStart = newFrameTime;

    InputManager::GetInstance().Update();

    state->Update(dt);

    state->Render();

    SDL_RenderPresent(renderer);

    SDL_Delay(33);
  };

  Resources::ClearImages();
  Resources::ClearMusics();
  Resources::ClearSounds();
}

Game &Game::GetInstance() {
  if (instance == nullptr) {
    std::string title = std::string("Brenno - 190127465");
    instance = new Game(title, 1024, 600);
  }

  return *instance;
}

float Game::GetDeltaTime() { return dt; }
