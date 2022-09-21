#include "Game.h"
#include "InputManager.h"
#include "Resources.h"
#include "common.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

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

  CHECK_ERROR_INT(TTF_Init());

  Mix_AllocateChannels(8);

  SDL_Window *window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, 0);

  CHECK_ERROR(window);

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE
      // | SDL_RENDERER_ACCELERATED
      // | SDL_RENDERER_PRESENTVSYNC
  );

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  CHECK_ERROR(renderer);

  storedState = nullptr;
}

Game::~Game() {
  if (storedState != nullptr) {
    delete storedState;
  }

  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

State &Game::GetState() { return *(stateStack.top().get()); }

void Game::Push(State *state) {
  if (instance->storedState != nullptr) {
    delete instance->storedState;
  }

  instance->storedState = state;
}

SDL_Renderer *Game::GetRenderer() { return renderer; }

void Game::Run() {
  if (storedState != nullptr) {
    stateStack.emplace(storedState);
    storedState = nullptr;
    stateStack.top()->Start();
  }

  while (!stateStack.empty() && !stateStack.top()->QuitRequested()) {
    // check if there is a state to be popped
    if (stateStack.top()->PopRequested()) {
      stateStack.pop();
      if (stateStack.empty()) {
        break;
      }
      stateStack.top()->Resume();
    }

    // check if there is a state to be pushed
    if (storedState != nullptr) {
      stateStack.top()->Pause();
      stateStack.emplace(storedState);
      storedState = nullptr;
      stateStack.top()->Start();
    }

    int newFrameTime = SDL_GetTicks();

    dt = (newFrameTime - frameStart) / 1000.0f;
    frameStart = newFrameTime;

    InputManager::GetInstance().Update();

    stateStack.top()->Update(dt);

    stateStack.top()->Render();

    SDL_RenderPresent(renderer);
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
