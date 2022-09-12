#ifndef __PENGUIN_CANNON_H
#define __PENGUIN_CANNON_H

#include "Component.h"
#include "GameObject.h"
#include "Timer.h"

#include <memory>

class PenguinCannon : public Component {
public:
  PenguinCannon(GameObject &associated);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void Shoot();
private:
  std::weak_ptr<GameObject> penguinBody;
  Timer shootCooldown;
  float angle;
};

#endif // __PENGUIN_CANNON_H
