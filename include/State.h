#ifndef __STATE_H
#define __STATE_H

#include <memory>
#include <string>
#include <vector>

#include "Music.h"
#include "Sprite.h"

class State {
public:
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();

private:
  void Input();
  void AddObject(int mouseX, int mouseY);

  Music music;
  bool quitRequested;

  std::vector<std::unique_ptr<GameObject>> gameObjects;
};

#endif // __STATE_H
