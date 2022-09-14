#ifndef __MINION_H
#define __MINION_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <memory>

class Minion : public Component {
public:
  Minion(GameObject &associated, std::weak_ptr<GameObject>, float arcOffsetDeg);

  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void NotifyCollision(GameObject &other) override;

  void Shoot(Vec2 target);

private:
  std::weak_ptr<GameObject> alienCenter;
  float arc;
  int hp;
};

#endif // __MINION_H
