#include "PenguinBody.h"
#include "Game.h"
#include "InputManager.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include <cmath>

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated) {
  speed = Vec2(0, 0);
  linearSpeed = 0;
  angle = 0;
  hp = 30;

  Sprite *sprite = new Sprite(associated, "assets/img/penguin.png");
  associated.AddComponent(sprite);

  PenguinBody::player = this;
}

PenguinBody::~PenguinBody() { PenguinBody::player = nullptr; }

void PenguinBody::Start() {
  GameObject *cannonGO = new GameObject();
  PenguinCannon *cannon = new PenguinCannon(*cannonGO);
  cannonGO->AddComponent(cannon);

  penguinCannon = Game::GetInstance().GetState().AddObject(cannonGO);
}

void PenguinBody::Update(float dt) {
  if (hp <= 0) {
    associated.RequestDelete();
    penguinCannon.lock()->RequestDelete();
    return;
  }

  InputManager &input = InputManager::GetInstance();

  if (input.IsKeyDown(SDLK_a)) {
    angle -= 4 * dt;
  }
  if (input.IsKeyDown(SDLK_d)) {
    angle += 4 * dt;
  }
  if (input.IsKeyDown(SDLK_w)) {
    linearSpeed += 10;
  }
  if (input.IsKeyDown(SDLK_s)) {
    linearSpeed -= 10;
  }

  speed = Vec2(linearSpeed, linearSpeed).GetRotated(angle - M_PI / 4);
  associated.angleDeg = angle * 180 / M_PI;

  associated.box.x += speed.x * dt;
  associated.box.y += speed.y * dt;

  linearSpeed *= pow(0.99, dt * std::abs(linearSpeed));

  // TODO: set penguinCannon position and angle
}

void PenguinBody::Render() {}
bool PenguinBody::Is(std::string type) { return type == "PenguinBody"; }

Vec2 PenguinBody::GetCenter() { return associated.GetPosition(); }
