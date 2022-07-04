#ifndef __SOUND_H
#define __SOUND_H

#include "Component.h"
#include <SDL2/SDL_mixer.h>

class Sound : public Component {
public:
  Sound(GameObject &associated);
  Sound(GameObject &associated, std::string file);
  ~Sound();

  void Play(int times = 1);
  void Stop();
  void Open(std::string file);
  bool IsOpen();

  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;

private:
  Mix_Chunk *chunk;
  int channel;
};

#endif // __SOUND_H
