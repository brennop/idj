#include "State.h"
#include "Face.h"
#include "Game.h"
#include "InputManager.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Vec2.h"
#include "Camera.h"
#include "CameraFollower.h"

#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <cstdio>

#define PI 3.14159265

State::State() {
  quitRequested = false;

  GameObject *go = new GameObject();

  Sprite *bg = new Sprite(*go);
  go->AddComponent(bg);

  CameraFollower *cam = new CameraFollower(*go);
  go->AddComponent(cam);

  music = *new Music();

  // map
  TileSet *tileSet = new TileSet(64, 64, "assets/img/tileset.png");
  TileMap *tileMap = new TileMap(*go, "assets/map/tileMap.txt", tileSet);

  go->AddComponent(tileMap);

  gameObjects.emplace_back(go);

  LoadAssets();
}

void State::LoadAssets() {
  GameObject *go = static_cast<GameObject *>(gameObjects[0].get());
  Sprite *bg = static_cast<Sprite *>(go->GetComponent("Sprite"));
  bg->Open("./assets/img/ocean.jpg");

  music.Open("./assets/audio/stageState.ogg");
  music.Play();
}

void State::Update(float dt) {
  InputManager &input = InputManager::GetInstance();

  if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested())
    quitRequested = true;

  if (input.KeyPress(SDLK_SPACE)) {
    Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) +
                  Vec2(input.GetMouseX(), input.GetMouseY());
    AddObject((int)objPos.x, (int)objPos.y);
  }

  Camera::Update(dt);

  // Update all game objects
  for (auto &gameObject : gameObjects) {
    gameObject->Update(dt);
  }

  // Remove all game objects marked for deletion
  for (auto it = gameObjects.begin(); it != gameObjects.end();) {
    if ((*it)->IsDead()) {
      it = gameObjects.erase(it);
    } else {
      it++;
    }
  }
}

void State::Render() {
  for (auto &gameObject : gameObjects) {
    gameObject->Render();
  }
}

void State::AddObject(int mouseX, int mouseY) {
  GameObject *enemy = new GameObject();

  Sprite *peguinface = new Sprite(*enemy, "./assets/img/penguinface.png");
  enemy->AddComponent(peguinface);

  enemy->box.x = mouseX + Camera::pos.x;
  enemy->box.y = mouseY + Camera::pos.y;

  Sound *sound = new Sound(*enemy, "./assets/audio/boom.wav");
  enemy->AddComponent(sound);

  Face *face = new Face(*enemy);
  enemy->AddComponent(face);

  gameObjects.emplace_back(enemy);
}

bool State::QuitRequested() { return quitRequested; }

State::~State() { gameObjects.clear(); }
