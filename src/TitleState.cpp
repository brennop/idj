#include "TitleState.h"
#include "Camera.h"
#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Sprite.h"
#include "StageState.h"
#include "Text.h"

TitleState::TitleState() : State() {
  GameObject *go = new GameObject();
  Sprite *bg = new Sprite(*go, "assets/img/title.jpg");
  go->AddComponent(bg);
  objectArray.emplace_back(go);

  go = new GameObject();
  Text *text = new Text(*go, "assets/font/Call me maybe.ttf", 40, Text::SOLID,
                        "Pressione ESPACO para continuar", {255, 255, 255, 255});
  go->AddComponent(text);
  go->box.x = 20;
  go->box.y = 520;
  objectArray.emplace_back(go);
}

TitleState::~TitleState() {}

void TitleState::LoadAssets() {}

void TitleState::Update(float dt) {
  if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
    Game::GetInstance().Push(new StageState());
  }

  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) ||
      InputManager::GetInstance().QuitRequested()) {
    quitRequested = true;
  }
}

void TitleState::Render() {
  RenderArray();
}

void TitleState::Start() {
  LoadAssets();
  StartArray();
}

void TitleState::Pause() {}

void TitleState::Resume() {}
