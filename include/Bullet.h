#ifndef __BULLET_H
#define __BULLET_H

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
  Bullet(GameObject &associated, float angle, float speed, int damage,
         float maxDistance, std::string sprite, bool targetsPlayer);

  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void NotifyCollision(GameObject &other) override;
  int GetDamage();

  bool targetsPlayer;

private:
  Vec2 speed;
  int damage;
  float distanceLeft;
};

#endif // __BULLET_H
