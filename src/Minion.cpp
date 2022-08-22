#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "State.h"
#include "Game.h"
#include "Camera.h"

static float randomRange(float min, float max) {
  return min + (max - min) * ((float) rand()) / (float) RAND_MAX;
}

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter,
               float arcOffset)
    : Component(associated), alienCenter(alienCenter), arc(arcOffset) {

  Sprite *sprite = new Sprite(associated, "./assets/img/minion.png");
  associated.AddComponent(sprite);
  float scale = randomRange(0.5, 1.0);
  sprite->SetScale(Vec2(scale, scale));
}

void Minion::Update(float dt) {
  Vec2 minionPos = Vec2(150.0, 0.0).GetRotated(arc);
  Vec2 alienPos = alienCenter.lock()->GetPosition();
  Vec2 target = alienPos + minionPos;

  arc += dt * M_PI * 2 / 10;

  associated.angleDeg = (associated.GetPosition() - alienCenter.lock()->GetPosition()).angle() * 180 /
                        M_PI;
  associated.SetPosition(target);
}

void Minion::Render() {}

bool Minion::Is(std::string type) { return type == "Minion"; }

void Minion::Shoot(Vec2 target) {
  GameObject *bullet = new GameObject();

  float angle = (target - associated.GetPosition()).angle();

  bullet->AddComponent(new Bullet(*bullet, angle, 300, 1, 1000, "./assets/img/minionbullet2.png"));
  bullet->SetPosition(associated.GetPosition());

  Game::GetInstance().GetState().AddObject(bullet);
}
