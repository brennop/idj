#ifndef __FACE_H
#define __FACE_H

#include "Component.h"

class Face : public Component {
public:
  Face(GameObject &associated);
  void Damage(int damage);

  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;

private:
  int hp;
};

#endif // __FACE_H
