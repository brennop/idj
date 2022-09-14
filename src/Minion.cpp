#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "State.h"
#include "Game.h"
#include "Camera.h"
#include "Collider.h"

static float randomRange(float min, float max) {
  return min + (max - min) * ((float) rand()) / (float) RAND_MAX;
}

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter,
               float arcOffset)
    : Component(associated), alienCenter(alienCenter), arc(arcOffset) {

  Sprite *sprite = new Sprite(associated, "./assets/img/minion.png");
  associated.AddComponent(sprite);

  Collider *collider = new Collider(associated);
  associated.AddComponent(collider);

  float scale = randomRange(0.5, 1.0);
  sprite->SetScale(Vec2(scale, scale));

  hp = 10;
}

void Minion::Update(float dt) {
  Vec2 minionPos = Vec2(150.0, 0.0).GetRotated(arc);
  Vec2 alienPos = alienCenter.lock() ? alienCenter.lock()->GetPosition() : Vec2(0,0);
  Vec2 target = alienPos + minionPos;

  arc += dt * M_PI * 2 / 10;

  associated.angleDeg = (associated.GetPosition() - alienPos).angle() * 180 /
                        M_PI;
  associated.SetPosition(target);

  if (hp <= 0) {
    associated.RequestDelete();

    GameObject *go = new GameObject();
    go->box.x = associated.box.x;
    go->box.y = associated.box.y;
    go->AddComponent(new Sprite(*go, "assets/img/miniondeath.png", 4, 0.1, 0.4));

    Game::GetInstance().GetState().AddObject(go);
  }
}

void Minion::Render() {}

bool Minion::Is(std::string type) { return type == "Minion"; }

void Minion::Shoot(Vec2 target) {
  GameObject *bullet = new GameObject();

  float angle = (target - associated.GetPosition()).angle();

  bullet->AddComponent(new Bullet(*bullet, angle, 300, 1, 1000, "./assets/img/minionbullet2.png", true));
  bullet->SetPosition(associated.GetPosition());

  Game::GetInstance().GetState().AddObject(bullet);
}

void Minion::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet") != nullptr) {
    Bullet *bullet = (Bullet *)other.GetComponent("Bullet");
    if (!bullet->targetsPlayer) {
      hp -= bullet->GetDamage();
    }
  }
}
