#include "Rect.h"

Rect::Rect(float x, float y, float w, float h) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

bool Rect::Contains(float x, float y) {
  return (x >= this->x && x <= this->x + this->w && y >= this->y &&
          y <= this->y + this->h);
}

Vec2 Rect::GetCenter() { return Vec2(x + w / 2, y + h / 2); }
