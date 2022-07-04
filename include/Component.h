#ifndef __COMPONENT_H
#define __COMPONENT_H

#include <string>

class Component;

#include "GameObject.h"

class Component {
public:
  Component(GameObject &associated);
  virtual ~Component();
  virtual void Update(float dt) = 0;
  virtual void Render() = 0;
  virtual bool Is(std::string type) = 0;

protected:
  GameObject &associated;
};

#endif // __COMPONENT_H
