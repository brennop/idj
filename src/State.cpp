#include "State.h"
#include "Face.h"
#include "Game.h"
#include "Sound.h"
#include "Vec2.h"

#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#define PI 3.14159265

State::State() {
  quitRequested = false;

  GameObject *go = new GameObject();

  Sprite *bg = new Sprite(*go);
  go->AddComponent(bg);

  gameObjects.emplace_back(go);

  music = *new Music();

  LoadAssets();
}

void State::LoadAssets() {
  GameObject *go = static_cast<GameObject *>(gameObjects[0].get());
  Sprite *bg = static_cast<Sprite *>(go->GetComponent("Sprite"));
  bg->Open("assets/background.png");

  music.Open("assets/audio/stageState.ogg");
  music.Play();
}

void State::Input() {
  SDL_Event event;
  int mouseX, mouseY;

  // Obtenha as coordenadas do mouse
  SDL_GetMouseState(&mouseX, &mouseY);

  // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
  while (SDL_PollEvent(&event)) {

    // Se o evento for quit, setar a flag para terminação
    if (event.type == SDL_QUIT) {
      quitRequested = true;
    }

    // Se o evento for clique...
    if (event.type == SDL_MOUSEBUTTONDOWN) {

      // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
      for (int i = gameObjects.size() - 1; i >= 0; --i) {
        // Obtem o ponteiro e casta pra Face.
        GameObject *go = (GameObject *)gameObjects[i].get();
        // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
        // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
        // ao usar get(), violamos esse princípio e estamos menos seguros.
        // Esse código, assim como a classe Face, é provisório. Futuramente,
        // para chamar funções de GameObjects, use objectArray[i]->função()
        // direto.

        if (go->box.Contains((float)mouseX, (float)mouseY)) {
          Face *face = (Face *)go->GetComponent("Face");
          if (nullptr != face) {
            // Aplica dano
            face->Damage(std::rand() % 10 + 10);
            // Sai do loop (só queremos acertar um)
            break;
          }
        }
      }
    }
    if (event.type == SDL_KEYDOWN) {
      // Se a tecla for ESC, setar a flag de quit
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        quitRequested = true;
      }
      // Se não, crie um objeto
      else {
        Vec2 objPos =
            Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) +
            Vec2(mouseX, mouseY);
        AddObject((int)objPos.x, (int)objPos.y);
      }
    }
  }
}

void State::Update(float dt) {
  Input();

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

  enemy->box.x = mouseX;
  enemy->box.y = mouseY;

  Sound *sound = new Sound(*enemy, "./assets/audio/boom.wav");
  enemy->AddComponent(sound);

  Face *face = new Face(*enemy);
  enemy->AddComponent(face);

  gameObjects.emplace_back(enemy);
}

bool State::QuitRequested() { return quitRequested; }

State::~State() { gameObjects.clear(); }
