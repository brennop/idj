#include "Music.h"

#include <SDL2/SDL_mixer.h>
#include <string>

Music::Music() { music = nullptr; }

Music::Music(std::string file) { Open(file); }

void Music::Play(int times) {
  if (IsOpen()) {
    Mix_PlayMusic(music, times);
  }
}

void Music::Stop(int msToStop) {
  if(IsOpen()) {
    Mix_FadeOutMusic(msToStop);
  }
}

void Music::Open(std::string file) {
  if (IsOpen()) {
    Mix_FreeMusic(music);
  }

  music = Mix_LoadMUS(file.c_str());

  if (!IsOpen()) {
    exit(1); // TODO: handle errors
  }
}

bool Music::IsOpen() {
  return music != nullptr;
}

Music::~Music() {
  Stop(0);
  Mix_FreeMusic(music);
}
