#include "Bullet.h"
#include "Collider.h"
#include "Sprite.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage,
               float maxDistance, std::string sprite, bool targetsPlayer)
    : Component(associated) {
  this->damage = damage;
  this->distanceLeft = maxDistance;

  this->speed = Vec2(speed, 0).GetRotated(angle);

  this->targetsPlayer = targetsPlayer;

  associated.angleDeg = angle * 180 / M_PI;

  Sprite *_sprite = new Sprite(associated, sprite, 3, 0.16);
  associated.AddComponent(_sprite);

  Collider *collider = new Collider(associated);
  associated.AddComponent(collider);
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

void Bullet::NotifyCollision(GameObject &other) {
  if (targetsPlayer) {
    if (other.GetComponent("PenguinBody") != nullptr ||
        other.GetComponent("PenguinCannon") != nullptr) {
      associated.RequestDelete();
    }
  } else {
    if (other.GetComponent("Alien") != nullptr ||
        other.GetComponent("Minion") != nullptr) {
      associated.RequestDelete();
    }
  }
}

int Bullet::GetDamage() { return damage; }
