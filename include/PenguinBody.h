#ifndef __PENGUIN_BODY_H
#define __PENGUIN_BODY_H

#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

class PenguinBody : public Component {
public:
  PenguinBody(GameObject &associated);
  ~PenguinBody();

  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;

  static PenguinBody *player;

private:
  std::weak_ptr<GameObject> penguinCannon;
  Vec2 speed;
  float linearSpeed;
  float angle;
  int hp;
};

#endif // __PENGUIN_BODY_H
