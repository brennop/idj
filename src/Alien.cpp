#include "Alien.h"
#include "InputManager.h"
#include "Sprite.h"
#include <cstdio>

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {

  Sprite *sprite = new Sprite(associated, "./assets/img/alien.png");
  associated.AddComponent(sprite);

  speed = Vec2(1.0, 1.0);
  hp = 30;

  taskQueue = std::queue<Action>();
  minionArray = std::vector<std::weak_ptr<GameObject>>(nMinions);
}

void Alien::Start() {
  // TODO: add minions
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
    Vec2 objPos = Vec2(input.GetMouseX(), input.GetMouseY());
    // TODO: calculate pos
    // TODO: take camera into account
    AddAction(Action::SHOOT, objPos.x, objPos.y);
  }

  if (input.MousePress(MOUSE2)) {
    Vec2 objPos = Vec2(input.GetMouseX(), input.GetMouseY());
    // TODO: take camera into account
    // TODO: calculate pos
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
    case Action::SHOOT:
      // TODO: shoot
      taskQueue.pop();
      break;
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
