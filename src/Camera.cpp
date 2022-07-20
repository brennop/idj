#include "Camera.h"
#include "InputManager.h"
#include <cstdio>

GameObject *Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(300, 300);

void Camera::Follow(GameObject *_focus) { focus = _focus; }
void Camera::Unfollow() { focus = nullptr; }

void Camera::Update(float dt) {
  if (focus) {
    /* pos = focus->pos + focus->size / 2; */
  } else {
    InputManager &input = InputManager::GetInstance();

    if (input.IsKeyDown(UP_ARROW_KEY)) {
      pos.y -= speed.y * dt;
    }
    if (input.IsKeyDown(DOWN_ARROW_KEY)) {
      pos.y += speed.y * dt;
    }
    if (input.IsKeyDown(LEFT_ARROW_KEY)) {
      pos.x -= speed.x * dt;
    }
    if (input.IsKeyDown(RIGHT_ARROW_KEY)) {
      pos.x += speed.x * dt;
    }
  }
}
