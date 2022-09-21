#include "EndState.h"
#include "Game.h"
#include "InputManager.h"
#include "Sprite.h"

EndState::EndState() {
  GameObject *go = new GameObject();
  Sprite *bg;
  if (Game::GetInstance().playerVictory) {
    bg = new Sprite(*go, "assets/img/win.jpg");
  } else {
    bg = new Sprite(*go, "assets/img/lose.jpg");
  }
  go->AddComponent(bg);
  objectArray.emplace_back(go);
}

EndState::~EndState() {}

void EndState::LoadAssets() {
  if (Game::GetInstance().playerVictory) {
    backgroundMusic.Open("assets/audio/endStateWin.ogg");
  } else {
    backgroundMusic.Open("assets/audio/endStateLose.ogg");
  }
}

void EndState::Update(float dt) {
  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) ||
      InputManager::GetInstance().QuitRequested()) {
    quitRequested = true;
  }
  if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
    popRequested = true;
  }
}

void EndState::Render() { RenderArray(); }

void EndState::Start() {
  LoadAssets();
  StartArray();
  backgroundMusic.Play(-1);
}

void EndState::Pause() {}

void EndState::Resume() {}
