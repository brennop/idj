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
  Sprite(GameObject &associated, std::string file, int frameCount,
         float frameTime);
  ~Sprite();

  void Open(std::string file);
  void SetClip(int x, int y, int w, int h);

  int GetWidth();
  int GetHeight();

  void Render() override;
  void Render(int x, int y);
  void Update(float dt) override;
  bool Is(std::string type) override;

  void SetScale(Vec2 scale);
  Vec2 GetScale();

  /*
   * Retorna true se texture estiver alocada
   */
  bool IsOpen();

  void SetFrame(int frame);
  void SetFrameCount(int frameCount);
  void SetFrameTime(float frameTime);

private:
  SDL_Texture *texture;
  int width;
  int height;
  SDL_Rect clipRect;
  Vec2 scale;

  int frameCount;
  int currentFrame;
  float timeElapsed;
  float frameTime;
};

#endif // __SPRITE_H
