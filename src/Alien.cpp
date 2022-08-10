#include "Alien.h"
#include "Game.h"
#include "InputManager.h"
#include "Minion.h"
#include "Sprite.h"
#include "State.h"

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {
  Sprite *sprite = new Sprite(associated, "./assets/img/alien.png");
  associated.AddComponent(sprite);

  speed = Vec2(1.0, 1.0);
  hp = 30;

  taskQueue = std::queue<Action>();
  minionArray = std::vector<std::weak_ptr<GameObject>>(nMinions);
}

void Alien::Start() {
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
  InputManager &input = InputManager::GetInstance();

  if (hp <= 0) {
    associated.RequestDelete();
  }

  if (input.MousePress(MOUSE1)) {
    Vec2 objPos = input.GetMousePos();
    AddAction(Action::SHOOT, objPos.x, objPos.y);
  }

  if (input.MousePress(MOUSE2)) {
    Vec2 objPos = input.GetMousePos();
    AddAction(Action::MOVE, objPos.x, objPos.y);
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
      // get random minion
      auto minion = minionArray[rand() % minionArray.size()].lock();
      if (minion) {
        static_cast<Minion *>(minion->GetComponent("Minion"))->Shoot(action.pos);
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

Alien::Action::Action(Action::ActionType type, float x, float y) {
  this->type = type;
  this->pos = Vec2(x, y);
}
