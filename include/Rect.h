#ifndef __RECT_H
#define __RECT_H

#include <Vec2.h>

class Rect {
public:
  float x, y, w, h;
  Rect(float x, float y, float w, float h);
  bool Contains(float x, float y);
  Vec2 GetCenter();
};

#endif // __RECT_H
