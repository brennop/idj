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
Vec2 Vec2::operator-(Vec2 v) { return Vec2(x - v.x, y - v.y); }
Vec2 Vec2::operator*(float f) { return Vec2(x * f, y * f); }

Vec2 Vec2::GetRotated(float angle) {
  float s = sin(angle);
  float c = cos(angle);
  return Vec2(x * c - y * s, x * s + y * c);
}

Vec2 Vec2::GetNormalized() {
  float l = length();
  return Vec2(x / l, y / l);
}

float Vec2::length() { return sqrt(x * x + y * y); }

float Vec2::angle() { return atan2(y, x); }

float Vec2::distance(Vec2 v) {
  return sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
}

float Vec2::distanceSquared(Vec2 v) {
  return (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y);
}



