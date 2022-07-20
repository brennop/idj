#include "Vec2.h"
#include <math.h>

Vec2::Vec2() {
  x = 0;
  y = 0;
}

Vec2::Vec2(float x, float y) {
  this->x = x;
  this->y = y;
}

Vec2 Vec2::operator+(Vec2 v) { return Vec2(x + v.x, y + v.y); }

Vec2 Vec2::GetRotated(float angle) {
  float s = sin(angle);
  float c = cos(angle);
  return Vec2(x * c - y * s, x * s + y * c);
}
