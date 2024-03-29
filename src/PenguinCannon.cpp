#include "PenguinCannon.h"
#include "InputManager.h"
#include "PenguinBody.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"

#define COOLDOWN 0.4f

PenguinCannon::PenguinCannon(GameObject &associated) : Component(associated) {
  Sprite *sprite = new Sprite(associated, "assets/img/cubngun.png");
  associated.AddComponent(sprite);

  Collider *collider = new Collider(associated);
  associated.AddComponent(collider);
}

void PenguinCannon::Update(float dt) {
  if (PenguinBody::player == nullptr) {
    associated.RequestDelete();
    return;
  }

  shootCooldown.Update(dt);

  Vec2 bodyPos = PenguinBody::player->GetCenter();
  associated.box.x = bodyPos.x - associated.box.w / 2;
  associated.box.y = bodyPos.y - associated.box.h / 2;

  InputManager &input = InputManager::GetInstance();

  angle = (input.GetMousePos() - associated.GetPosition()).angle();
  associated.angleDeg = angle * 180 / M_PI;

  if (input.MousePress(MOUSE1)) {
    Shoot();
  }
}
void PenguinCannon::Render() {}
bool PenguinCannon::Is(std::string type) { return type == "PenguinCannon"; }

void PenguinCannon::Shoot() {
  if (shootCooldown.Get() < COOLDOWN) {
    return;
  }

  shootCooldown.Restart();

  GameObject *bullet = new GameObject();

  bullet->AddComponent(new Bullet(*bullet, angle, 300, 5, 1000, "./assets/img/penguinbullet.png", false));
  bullet->SetPosition(associated.GetPosition());

  Game::GetInstance().GetState().AddObject(bullet);
}
