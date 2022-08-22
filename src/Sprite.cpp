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
  scale = Vec2(1.0, 1.0);
}

Sprite::Sprite(GameObject &associated, std::string file)
    : Component(associated) {
  texture = nullptr;
  scale = Vec2(1.0, 1.0);
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

void Sprite::Render(int x, int y, int z) {
  Game &game = Game::GetInstance();
  game.GetState().enqueueRender(z, &associated);
}

void Sprite::Render() { Render(associated.GetBox().x, associated.GetBox().y); }

void Sprite::Render(int x, int y) {
  Game &game = Game::GetInstance();
  auto *renderer = game.GetRenderer();

  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = clipRect.w * scale.x;
  dstrect.h = clipRect.h * scale.y;

  int render = SDL_RenderCopyEx(renderer, texture, &clipRect, &dstrect,
                                associated.angleDeg, nullptr,
                                SDL_FLIP_NONE);
  CHECK_ERROR_INT(render);
}


void Sprite::Update(float dt) {}
bool Sprite::Is(std::string type) { return type == "Sprite"; }

int Sprite::GetWidth() { return width * scale.x; }

int Sprite::GetHeight() { return height * scale.y; }

void Sprite::SetScale(Vec2 scale) { this->scale = scale; }
Vec2 Sprite::GetScale() { return scale; }

bool Sprite::IsOpen() { return texture != nullptr; }
