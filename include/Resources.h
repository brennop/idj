#ifndef __RESOURCES_H
#define __RESOURCES_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <string>
#include <unordered_map>

class Resources {
public:
  static SDL_Texture *GetImage(const char *filePath);
  static void ClearImages();

  static Mix_Music *GetMusic(const char *filePath);
  static void ClearMusics();

  static Mix_Chunk *GetSound(const char *filePath);
  static void ClearSounds();

private:
  static std::unordered_map<std::string, SDL_Texture *> imageTable;
  static std::unordered_map<std::string, Mix_Music *> musicTable;
  static std::unordered_map<std::string, Mix_Chunk *> soundTable;
};

#endif // __RESOURCES_H
