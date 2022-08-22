#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage,
               float maxDistance, std::string sprite)
    : Component(associated) {
  this->damage = damage;
  this->distanceLeft = maxDistance;

  this->speed = Vec2(speed, 0).GetRotated(angle);

  associated.angleDeg = angle * 180 / M_PI;

  Sprite *_sprite = new Sprite(associated, sprite, 3, 0.16);
  associated.AddComponent(_sprite);
}

void Bullet::Update(float dt) {
  associated.box.x += speed.x * dt;
  associated.box.y += speed.y * dt;
  distanceLeft -= speed.length() * dt;
  if (distanceLeft < 0) {
    associated.RequestDelete();
  }
}

void Bullet::Render() {}

bool Bullet::Is(std::string type) { return type == "Bullet"; }

int Bullet::GetDamage() { return damage; }
