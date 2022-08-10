#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "State.h"
#include "Game.h"
#include "Camera.h"

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter,
               float arcOffset)
    : Component(associated), alienCenter(alienCenter), arc(arcOffset) {

  Sprite *sprite = new Sprite(associated, "./assets/img/minion.png");
  associated.AddComponent(sprite);
}

void Minion::Update(float dt) {
  Vec2 minionPos = Vec2(200.0, 0.0).GetRotated(arc);
  Vec2 alienPos = alienCenter.lock()->GetPosition();
  Vec2 target = alienPos + minionPos;

  arc += dt * M_PI * 2 / 10;

  associated.SetPosition(target);
}

void Minion::Render() {}

bool Minion::Is(std::string type) { return type == "Minion"; }

void Minion::Shoot(Vec2 target) {
  GameObject *bullet = new GameObject();

  float angle = (target - associated.GetPosition()).angle();

  bullet->AddComponent(new Bullet(*bullet, angle, 500, 1, 1000, "./assets/img/minionbullet1.png"));
  bullet->SetPosition(associated.GetPosition());

  Game::GetInstance().GetState().AddObject(bullet);
}
