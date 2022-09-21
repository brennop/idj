#include "StageState.h"
#include "Alien.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Collider.h"
#include "Collision.h"
#include "Face.h"
#include "Game.h"
#include "InputManager.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Vec2.h"
#include "EndState.h"

#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <cstdio>

#define PI 3.14159265

StageState::StageState() : State() {
  quitRequested = false;
  started = false;

  backgroundMusic = *new Music();

  /**
   * resources game object
   */
  GameObject *go = new GameObject();

  Sprite *bg = new Sprite(*go);
  go->AddComponent(bg);

  CameraFollower *cam = new CameraFollower(*go);
  go->AddComponent(cam);

  TileSet *tileSet = new TileSet(64, 64, "assets/img/tileset.png");
  TileMap *tileMap = new TileMap(*go, "assets/map/tileMap.txt", tileSet);

  go->AddComponent(tileMap);

  objectArray.emplace_back(go);

  /**
   * player game object
   */
  GameObject *playerGo = new GameObject();
  playerGo->box.x = 704;
  playerGo->box.y = 640;

  Camera::Follow(playerGo);

  PenguinBody *player = new PenguinBody(*playerGo);
  playerGo->AddComponent(player);

  objectArray.emplace_back(playerGo);

  GameObject *alienGo = new GameObject();
  alienGo->box.x = 512 + Camera::pos.x;
  alienGo->box.y = 100 + Camera::pos.y;

  Alien *alien = new Alien(*alienGo, 4);
  alienGo->AddComponent(alien);

  objectArray.emplace_back(alienGo);
}

StageState::~StageState() {
  Camera::Unfollow();
  Camera::pos = {0, 0};
}

void StageState::LoadAssets() {
  GameObject *go = static_cast<GameObject *>(objectArray[0].get());
  Sprite *bg = static_cast<Sprite *>(go->GetComponent("Sprite"));
  bg->Open("./assets/img/ocean.jpg");

  backgroundMusic.Open("./assets/audio/stageState.ogg");
}

void StageState::Start() {
  LoadAssets();
  backgroundMusic.Play();

  StartArray();
}

void StageState::Update(float dt) {
  InputManager &input = InputManager::GetInstance();

  if (input.QuitRequested())
    quitRequested = true;

  if (input.KeyPress(ESCAPE_KEY))
    popRequested = true;

  Camera::Update(dt);

  UpdateArray(dt);

  // check collisions
  for (unsigned i = 0; i < objectArray.size(); i++) {
    for (unsigned j = i + 1; j < objectArray.size(); j++) {
      Collider *collider1 =
          static_cast<Collider *>(objectArray[i]->GetComponent("Collider"));
      Collider *collider2 =
          static_cast<Collider *>(objectArray[j]->GetComponent("Collider"));

      if (collider1 && collider2) {
        if (Collision::IsColliding(collider1->box, collider2->box,
                                   objectArray[i]->angleDeg,
                                   objectArray[j]->angleDeg)) {
          objectArray[i]->NotifyCollision(*objectArray[j]);
          objectArray[j]->NotifyCollision(*objectArray[i]);
        }
      }
    }
  }

  // check if player is dead
  if (objectArray[1]->IsDead()) {
    popRequested = true;
    Game::GetInstance().playerVictory = false;
    Game::GetInstance().Push(new EndState());
  }

  // check if alien is dead
  if (objectArray[2]->IsDead()) {
    popRequested = true;
    Game::GetInstance().playerVictory = true;
    Game::GetInstance().Push(new EndState());
  }

  // Remove all game objects marked for deletion
  for (int i = objectArray.size() - 1; i >= 0; i--) {
    if (objectArray[i]->IsDead()) {
      objectArray.erase(objectArray.begin() + i);
    }
  }
}

void StageState::Render() { RenderArray(); }

void StageState::Pause() {}
void StageState::Resume() {}
