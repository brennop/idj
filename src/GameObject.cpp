#include "GameObject.h"
#include "Camera.h"

#include <algorithm>

GameObject::GameObject() : box(0, 0, 0, 0) {
  isDead = false;

  started = false;
}

GameObject::~GameObject() { components.clear(); }

void GameObject::Start() { 
  for (auto &c : components) {
    c->Start();
  }

  started = true; 
}

void GameObject::Update(float dt) {
  for (auto &component : components) {
    component->Update(dt);
  }
}

void GameObject::Render() {
  for (auto &component : components) {
    component->Render();
  }
}

bool GameObject::IsDead() { return isDead; }

void GameObject::RequestDelete() { isDead = true; }

void GameObject::AddComponent(Component *component) {
  if(started) {
    component->Start();
  }
  components.emplace_back(component);
}

void GameObject::RemoveComponent(Component *component) {
  std::remove_if(
      components.begin(), components.end(),
      [=](std::unique_ptr<Component> &c) { return c.get() == component; });
}

Rect GameObject::GetBox() {
  return Rect(box.x - Camera::pos.x, box.y - Camera::pos.y, box.w, box.h);
}

Vec2 GameObject::GetPosition() {
  return Vec2(box.x + box.w / 2, box.y + box.h / 2);
}

void GameObject::SetPosition(Vec2 position) {
  box.x = position.x - box.w / 2;
  box.y = position.y - box.h / 2;
}

Component *GameObject::GetComponent(std::string type) {
  for (auto &component : components) {
    if (component->Is(type)) {
      return component.get();
    }
  }
  return nullptr;
}
