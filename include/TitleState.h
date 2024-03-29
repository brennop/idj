#ifndef __TITLESTATE_H
#define __TITLESTATE_H

#include "State.h"

class TitleState : public State {
public:
  TitleState();
  ~TitleState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void Start();
  void Pause();
  void Resume();
};

#endif // __TITLESTATE_H
