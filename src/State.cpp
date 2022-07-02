#include "State.h"
#include "Game.h"

#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

State::State() {
  quitRequested = false;
  bg = *new Sprite();
  music = *new Music();

  LoadAssets();
}

void State::LoadAssets() {
  bg.Open("assets/img/ocean.jpg");
  music.Open("assets/audio/stageState.ogg");
  music.Play();
}

void State::Update(float dt) {
  if(SDL_QuitRequested()) {
    quitRequested = true;
  }
}

void State::Render() {
  bg.Render(0, 0);
}

bool State::QuitRequested() {
  return quitRequested;
}
