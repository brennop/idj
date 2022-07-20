#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "common.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstdio>
#include <string>

Sprite::Sprite(GameObject &associated) : Component(associated) {
  texture = nullptr;
}

Sprite::Sprite(GameObject &associated, std::string file)
    : Component(associated) {
  texture = nullptr;
  Open(file);
}

Sprite::~Sprite() { }

void Sprite::Open(std::string file) {
  texture = Resources::GetImage(file.c_str());

  int query = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  associated.box.w = width;
  associated.box.h = height;

  CHECK_ERROR_INT(query);

  SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Render() { Render(associated.box.x, associated.box.y); }

void Sprite::Render(int x, int y) {
  Game &game = Game::GetInstance();
  auto *renderer = game.GetRenderer();

  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = clipRect.w;
  dstrect.h = clipRect.h;

  int render = SDL_RenderCopy(renderer, texture, &clipRect, &dstrect);
  CHECK_ERROR_INT(render);
}

void Sprite::Update(float dt) {}
bool Sprite::Is(std::string type) { return type == "Sprite"; }

int Sprite::GetWidth() { return width; }

int Sprite::GetHeight() { return height; }

bool Sprite::IsOpen() { return texture != nullptr; }
