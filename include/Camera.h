#ifndef __CAMERA_H
#define __CAMERA_H

#include "GameObject.h"
#include "Vec2.h"

class Camera
{
public:
  static void Follow(GameObject* focus);
  static void Unfollow();
  static void Update(float dt);

  static Vec2 pos;
  static Vec2 speed;
private:
  static GameObject* focus;
  static Vec2 accel;
  static Vec2 velocity;
  static float damping;
};

#endif // __CAMERA_H
