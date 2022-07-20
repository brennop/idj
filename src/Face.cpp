#include "Face.h"
#include "InputManager.h"
#include <cstdio>

Face::Face(GameObject &associated) : Component(associated) { hp = 30; }

void Face::Damage(int damage) {
  hp -= damage;

  if (hp <= 0) {
    associated.RequestDelete();
    // TODO: play sound
  }
}

void Face::Update(float dt) {
  InputManager &input = InputManager::GetInstance();
  if (input.MousePress(LEFT_MOUSE_BUTTON)) {
    if (associated.GetBox().Contains((float) input.GetMouseX(), (float) input.GetMouseY())) {
      Damage(std::rand() % 10 + 10);
    }
  };
}

void Face::Render() {}

bool Face::Is(std::string type) { return type == "Face"; }
