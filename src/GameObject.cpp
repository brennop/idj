#include "GameObject.h"

#include <algorithm>

GameObject::GameObject() : box(0, 0, 0, 0) { isDead = false; }

GameObject::~GameObject() { components.clear(); }

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
  components.emplace_back(component);
}

void GameObject::RemoveComponent(Component *component) {
  components.erase(std::remove(components.begin(), components.end(), component),
                   components.end());
}

Component *GameObject::GetComponent(std::string type) {
  auto result =
      find_if(components.begin(), components.end(),
              [type](Component *component) { return component->Is(type); });

  if (result != components.end()) {
    return result->get();
  }
  return nullptr;
}
