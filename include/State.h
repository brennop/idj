#ifndef __STATE_H
#define __STATE_H

#include <memory>
#include <string>
#include <vector>

#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"

class State {
public:
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();

  void Start();
  void Update(float dt);
  void Render();

  std::weak_ptr<GameObject> AddObject(GameObject* go);
  std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
private:
  void Input();
  void AddObject(int mouseX, int mouseY);

  Music music;
  bool quitRequested;

  bool started;

  std::vector<std::shared_ptr<GameObject>> gameObjects;
};

#endif // __STATE_H
