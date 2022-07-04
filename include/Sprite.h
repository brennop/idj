#ifndef __SPRITE_H
#define __SPRITE_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"

#include <string>

class Sprite : public Component {
public:
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, std::string file);
  ~Sprite();

  void Open(std::string file);
  void SetClip(int x, int y, int w, int h);

  int GetWidth();
  int GetHeight();

  void Render() override;
  void Update(float dt) override;
  bool Is(std::string type) override;

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
