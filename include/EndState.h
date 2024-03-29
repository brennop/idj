#ifndef __ENDSTATE_H
#define __ENDSTATE_H

#include "Music.h"
#include "State.h"

class EndState : public State {
public:
  EndState();
  ~EndState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void Start();
  void Pause();
  void Resume();

private:
  Music backgroundMusic;
};

#endif // __ENDSTATE_H
