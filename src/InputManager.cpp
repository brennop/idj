#include "InputManager.h"

#include "SDL2/SDL_events.h"
#include <SDL2/SDL_mouse.h>
#include <cstdio>

InputManager &InputManager::GetInstance() {
  static InputManager inputManager;
  return inputManager;
}

InputManager::~InputManager() {}

InputManager::InputManager() {
  for (int i = 0; i < 6; i++) {
    mouseState[i] = 0;
    mouseUpdate[i] = 0;
  }
  for (int i = 0; i < 416; i++) {
    keyState[i] = 0;
    keyUpdate[i] = 0;
  }
}

void InputManager::Update() {
  SDL_Event event;

  quitRequested = false;

  SDL_GetMouseState(&mouseX, &mouseY);

  updateCounter++;

  if(SDL_QuitRequested()) {
    quitRequested = true;
  }

  while (SDL_PollEvent(&event)) {
    if (event.key.repeat)
      continue;

    switch (event.type) {
    case SDL_QUIT:
      quitRequested = true;
      break;
    case SDL_MOUSEBUTTONDOWN:
      mouseState[event.button.button] = true;
      mouseUpdate[event.button.button] = updateCounter;
      break;
    case SDL_MOUSEBUTTONUP:
      mouseState[event.button.button] = false;
      mouseUpdate[event.button.button] = updateCounter;
      break;
    case SDL_KEYDOWN: {
      int keyCode = event.key.keysym.sym;
      if (keyCode >= 0x40000000) {
        keyCode -= 0x3FFFFF80;
      }
      keyState[keyCode] = true;
      keyUpdate[keyCode] = updateCounter;
      break;
    }
    case SDL_KEYUP: {
      int keyCode = event.key.keysym.sym;
      if (keyCode >= 0x40000000) {
        keyCode -= 0x3FFFFF80;
      }
      keyState[keyCode] = false;
      keyUpdate[keyCode] = updateCounter;
      break;
    }
    }
  }
}

int InputManager::GetMouseX() { return GetInstance().mouseX; }
int InputManager::GetMouseY() { return GetInstance().mouseY; }
bool InputManager::QuitRequested() { return GetInstance().quitRequested; }

bool InputManager::KeyPress(int key) {
  return keyUpdate[key] == updateCounter && keyState[key];
}

bool InputManager::KeyRelease(int key) {
  return keyUpdate[key] == updateCounter && !keyState[key];
}

bool InputManager::MousePress(int button) {
  return mouseUpdate[button] == updateCounter && mouseState[button];
}

bool InputManager::MouseRelease(int button) {
  return mouseUpdate[button] == updateCounter && !mouseState[button];
}

bool InputManager::IsKeyDown(int key) { return keyState[key]; }
bool InputManager::IsMouseDown(int button) { return mouseState[button]; }
