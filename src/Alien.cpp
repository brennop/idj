#include "Alien.h"
#include "Bullet.h"
#include "Collider.h"
#include "Game.h"
#include "InputManager.h"
#include "Minion.h"
#include "PenguinBody.h"
#include "Sprite.h"
#include "State.h"

#define DISTANCE_TO_MOVE 300
#define ALIEN_COOLDOWN 5.0f

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {
  Sprite *sprite = new Sprite(associated, "./assets/img/alien.png");
  associated.AddComponent(sprite);

  Collider *collider = new Collider(associated);
  associated.AddComponent(collider);

  speed = Vec2(1.0, 1.0);
  hp = 30;

  fireRate = 0.2f;
  fireAngle = 0.0f;

  taskQueue = std::queue<Action>();
  minionArray = std::vector<std::weak_ptr<GameObject>>(nMinions);
}

void Alien::Start() {
  state = MOVING;

  for (unsigned int i = 0; i < minionArray.size(); i++) {
    State &state = Game::GetInstance().GetState();

    auto alien = state.GetObjectPtr(&associated);
    float arcOffsetDeg = i * M_PI * 2 / minionArray.size();

    GameObject *go = new GameObject();
    Minion *minion = new Minion(*go, alien, arcOffsetDeg);
    go->AddComponent(minion);

    minionArray[i] = state.AddObject(go);
  }
}

Alien::~Alien() {
  // destroy minions
  // TODO: check this method
  minionArray.clear();
}

void Alien::Update(float dt) {
  associated.angleDeg += dt * 180 / M_PI * -1;

  if (hp <= 0) {
    associated.RequestDelete();

    GameObject *go = new GameObject();
    go->box.x = associated.box.x;
    go->box.y = associated.box.y;
    go->AddComponent(
        new Sprite(*go, "assets/img/aliendeath.png", 4, 0.1, 0.39));

    Game::GetInstance().GetState().AddObject(go);
  }

  stateTimer.Update(dt);
  shootCooldown.Update(dt);

  // distance from player
  auto player = PenguinBody::player;
  if (player != nullptr && stateTimer.Get() > ALIEN_COOLDOWN) {
    Vec2 playerPos = player->GetCenter();
    float angle = (playerPos - associated.GetPosition()).angle();
    Vec2 target = associated.GetPosition() + Vec2(300, 0).GetRotated(angle);
    taskQueue.push(Action(Action::MOVE, target.x, target.y));
    fireRate = 2.0f; // cooldown to shoot
    stateTimer.Restart();
    attackType = rand() % 3;
  } else if (player != nullptr && shootCooldown.Get() > fireRate) {
    Vec2 target;

    switch (attackType) {
    case 0: // shoot at player
      fireRate = 0.5f;
      target = player->GetCenter();
      taskQueue.push(Action(Action::SHOOT, target.x, target.y));
      break;
    case 1: // shotgun
      fireRate = 1.0f;
      for (int i = 0; i < 8; i++) {
        target = player->GetCenter();
        target = player->GetCenter() + Vec2(100, 0).GetRotated(fireAngle);
        fireAngle += 0.2f;
        taskQueue.push(Action(Action::SHOOT, target.x, target.y));
      }
      break;
    case 2: // shoot in circle
      fireRate = 0.15f;
      target = associated.GetPosition() + Vec2(300, 0).GetRotated(fireAngle);
      taskQueue.push(Action(Action::SHOOT, target.x, target.y));
      fireAngle += 0.1;
      break;
    }
    shootCooldown.Restart();
  }

  if (!taskQueue.empty()) {
    Action action = taskQueue.front();
    switch (action.type) {
    case Action::MOVE: {
      Vec2 diff = (action.pos - associated.GetPosition()) * 0.1;

      if (diff.length() < 0.1) {
        taskQueue.pop();
      } else {
        associated.box.x += diff.x * pow(0.9, dt * speed.x);
        associated.box.y += diff.y * pow(0.9, dt * speed.y);
      }

      break;
    }
    case Action::SHOOT: {
      if (minionArray.size() > 0) {
        int index = attackType % minionArray.size();
        auto minion = minionArray[index].lock();
        if (minion) {
          static_cast<Minion *>(minion->GetComponent("Minion"))
              ->Shoot(action.pos);
        }
      }
      taskQueue.pop();
      break;
    }
    default:
      taskQueue.pop();
      break;
    }
  }
}

void Alien::AddAction(Action::ActionType type, float x, float y) {
  taskQueue.push(Action(type, x, y));
}

bool Alien::Is(std::string type) { return type == "Alien"; }

void Alien::Render() {}

void Alien::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet")) {
    Bullet *bullet = (Bullet *)other.GetComponent("Bullet");
    if (!bullet->targetsPlayer) {
      hp -= bullet->GetDamage();
    }
  }
}

Alien::Action::Action(Action::ActionType type, float x, float y) {
  this->type = type;
  this->pos = Vec2(x, y);
}
