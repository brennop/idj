#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

class GameObject;

#include <vector>
#include <memory>

#include "Component.h"
#include "Rect.h"

class GameObject {
public:
  GameObject();
  ~GameObject();

  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component *component);
  void RemoveComponent(Component *component);
  Component *GetComponent(std::string type);
  Rect box;

private:
  bool isDead;
  std::vector<std::unique_ptr<Component>> components;
};

#endif // __GAMEOBJECT_H
