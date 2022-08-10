#ifndef _VEC2_H_
#define _VEC2_H_

class Vec2 {
public:
  float x, y;
  Vec2();
  Vec2(float x, float y);
  Vec2 operator+(Vec2 v);
  Vec2 operator-(Vec2 v);
  Vec2 operator*(float f);
  Vec2 operator/(float f);
  float operator*(Vec2 v);

  Vec2 GetRotated(float angle);
  Vec2 GetNormalized();
  float angle();

  float length();
  float dot(Vec2 v);
  float cross(Vec2 v);
  float distance(Vec2 v);
  float distanceSquared(Vec2 v);
};

#endif // _VEC2_H_
