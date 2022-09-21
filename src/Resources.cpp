#include "Resources.h"
#include "Game.h"
#include "common.h"

#include <string>
#include <unordered_map>

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable = {};
std::unordered_map<std::string, Mix_Music *> Resources::musicTable = {};
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable = {};
std::unordered_map<std::string, TTF_Font *> Resources::fontTable = {};

SDL_Texture *Resources::GetImage(const char *filePath) {
  if (imageTable.find(filePath) == imageTable.end()) {
    SDL_Renderer *renderer = Game::GetInstance().GetRenderer();
    SDL_Texture *texture = IMG_LoadTexture(renderer, filePath);
    CHECK_ERROR(texture);
    imageTable[filePath] = texture;
  }

  return imageTable[filePath];
}

void Resources::ClearImages() {
  for (auto &image : imageTable) {
    SDL_DestroyTexture(image.second);
  }
  imageTable.clear();
}

Mix_Music *Resources::GetMusic(const char *filePath) {
  if (musicTable.find(filePath) == musicTable.end()) {
    Mix_Music *music = Mix_LoadMUS(filePath);
    CHECK_ERROR(music);
    musicTable[filePath] = music;
  }

  return musicTable[filePath];
}

void Resources::ClearMusics() {
  for (auto &music : musicTable) {
    Mix_FreeMusic(music.second);
  }
  musicTable.clear();
}

Mix_Chunk *Resources::GetSound(const char *filePath) {
  if (soundTable.find(filePath) == soundTable.end()) {
    Mix_Chunk *sound = Mix_LoadWAV(filePath);
    CHECK_ERROR(sound);
    soundTable[filePath] = sound;
  }

  return soundTable[filePath];
}

void Resources::ClearSounds() {
  for (auto &sound : soundTable) {
    Mix_FreeChunk(sound.second);
  }
  soundTable.clear();
}

TTF_Font *Resources::GetFont(const char *filePath, int fontSize) {
  std::string key = std::string(filePath) + std::to_string(fontSize);
  if (fontTable.find(key) == fontTable.end()) {
    TTF_Font *font = TTF_OpenFont(filePath, fontSize);
    CHECK_ERROR(font);
    fontTable[key] = font;
  }

  return fontTable[key];
}

void Resources::ClearFonts() {
  for (auto &font : fontTable) {
    TTF_CloseFont(font.second);
  }
  fontTable.clear();
}
