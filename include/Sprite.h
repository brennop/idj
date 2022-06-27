#ifndef __SPRITE_H
#define __SPRITE_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <string>

class Sprite {
public:
  Sprite();
  Sprite(std::string file);
  ~Sprite();

  void Open(std::string file);
  void SetClip(int x, int y, int w, int h);
  void Render(int x, int y);
  int GetWidth();
  int GetHeight();

  /*
   * Retorna true se texture estiver alocada
   */
  bool IsOpen();

private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;
};

#endif // __SPRITE_H
