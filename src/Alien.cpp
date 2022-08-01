#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {

  Sprite *sprite = new Sprite(associated, "./assets/img/alien.png");
  associated.AddComponent(sprite);

  speed = Vec2(0.0, 0.0);
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

  if(input.MousePress(LEFT_MOUSE_BUTTON)) {
    Vec2 objPos = Vec2(input.GetMouseX(), input.GetMouseY());
    // TODO: calculate pos
    AddAction(Action::SHOOT, objPos.x, objPos.y);
  }


}

void Alien::AddAction(Action::ActionType type, float x, float y) {
  Action action(type, x, y);
  taskQueue.push(action);
}
