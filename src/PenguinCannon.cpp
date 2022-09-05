#include "PenguinCannon.h"
#include "Sprite.h"

PenguinCannon::PenguinCannon(GameObject &associated) : Component(associated) {
  Sprite *sprite = new Sprite(associated, "assets/img/penguin.png");
  associated.AddComponent(sprite);
}

void PenguinCannon::Update(float dt) {}
void PenguinCannon::Render() {}
bool PenguinCannon::Is(std::string type) { return type == "PenguinCannon"; }

void PenguinCannon::Shoot() {

}

