#ifndef __RESOURCES_H
#define __RESOURCES_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
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

  static TTF_Font *GetFont(const char *filePath, int fontSize);
  static void ClearFonts();
private:
  static std::unordered_map<std::string, SDL_Texture *> imageTable;
  static std::unordered_map<std::string, Mix_Music *> musicTable;
  static std::unordered_map<std::string, Mix_Chunk *> soundTable;
  static std::unordered_map<std::string, TTF_Font *> fontTable;
};

#endif // __RESOURCES_H
