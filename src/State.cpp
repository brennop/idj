#include "State.h"

State::State() {
  popRequested = false;
  quitRequested = false;
  started = false;
}

State::~State() { objectArray.clear(); }

void State::LoadAssets() {}

void State::Update(float dt) {}

void State::Render() {}

void State::Start() {}

void State::Pause() {}

void State::Resume() {}

std::weak_ptr<GameObject> State::AddObject(GameObject *object) {
  objectArray.emplace_back(object);

  if (started) {
    object->Start();
  }

  return objectArray.back();
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *object) {
  for (auto &it : objectArray) {
    if (it.get() == object) {
      return it;
    }
  }
  return std::weak_ptr<GameObject>();
}

bool State::PopRequested() { return popRequested; }

bool State::QuitRequested() { return quitRequested; }

void State::StartArray() {
  for (auto &it : objectArray) {
    it->Start();
  }
  started = true;
}

void State::UpdateArray(float dt) {
  for (unsigned int i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Update(dt);
  }
}

void State::RenderArray() {
  for (unsigned int i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Render();
  }
}
