#include "Sound.h"
#include "common.h"

Sound::Sound(GameObject &associated) : Component(associated) {
  chunk = nullptr;
}

Sound::Sound(GameObject &associated, std::string file) : Sound(associated) {
  Open(file);
}

void Sound::Open(std::string file) {
  if (chunk != nullptr) {
    Mix_FreeChunk(chunk);
  }

  chunk = Mix_LoadWAV(file.c_str());
  CHECK_ERROR(chunk);
}

void Sound::Play(int times) {
  if (chunk != nullptr) {
    channel = Mix_PlayChannel(-1, chunk, times - 1);
    CHECK_ERROR_INT(channel);
  }
}

void Sound::Stop() {
  if (chunk != nullptr) {
    Mix_HaltChannel(channel);
  }
}

void Sound::Update(float dt) { }
void Sound::Render() { }
bool Sound::Is(std::string type) { return type == "Sound"; }

Sound::~Sound() {
  if (chunk != nullptr) {
    Mix_HaltChannel(channel);
    Mix_FreeChunk(chunk);
  }
}
