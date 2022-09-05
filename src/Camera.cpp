#include "Camera.h"
#include "InputManager.h"
#include <cstdio>

GameObject *Camera::focus = nullptr;

Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(15, 15);
Vec2 Camera::velocity = Vec2(0, 0);
float Camera::damping = 0.7;

void Camera::Follow(GameObject *_focus) { focus = _focus; }
void Camera::Unfollow() { focus = nullptr; }

void Camera::Update(float dt) {
  if (focus) {
    Vec2 center = focus->GetPosition();
    Vec2 distance = center - pos - Vec2(512, 300);
    velocity = distance * 15;
  } else {
    InputManager &input = InputManager::GetInstance();

    if (input.IsKeyDown(UP_ARROW_KEY)) {
      velocity.y -= speed.y;
    }
    if (input.IsKeyDown(DOWN_ARROW_KEY)) {
      velocity.y += speed.y;
    }
    if (input.IsKeyDown(LEFT_ARROW_KEY)) {
      velocity.x -= speed.x;
    }
    if (input.IsKeyDown(RIGHT_ARROW_KEY)) {
      velocity.x += speed.x;
    }
  }

  // TODO: make diagonal movement slower

  pos.y += velocity.y * dt;
  pos.x += velocity.x * dt;

  // damping
  velocity.x *= pow(damping, dt * speed.x);
  velocity.y *= pow(damping, dt * speed.y);
}
