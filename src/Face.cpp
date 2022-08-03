#include "Face.h"
#include "InputManager.h"
#include "Sound.h"

Face::Face(GameObject &associated) : Component(associated) { hp = 30; }

void Face::Damage(int damage) {
  hp -= damage;

  if (hp <= 0) {
    associated.RequestDelete();
    // play sound
    static_cast<Sound *>(associated.GetComponent("Sound"))->Play();
  }
}

void Face::Update(float dt) { }

void Face::Render() {}

bool Face::Is(std::string type) { return type == "Face"; }
