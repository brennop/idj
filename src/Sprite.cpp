#include "Sprite.h"
#include "Game.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <string>

Sprite::Sprite() { texture = nullptr; }

Sprite::Sprite(std::string file) {
  texture = nullptr;
  Open(file);
}

Sprite::~Sprite() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }
}

void Sprite::Open(std::string file) {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }

  Game &game = Game::GetInstance();
  auto *renderer = game.GetRenderer();
  texture = IMG_LoadTexture(renderer, file.c_str());

  if (texture == nullptr) {
    // TODO: handle error
    exit(1);
  }
}

void Sprite::SetClip(int x, int y, int w, int h) {
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Render(int x, int y) {
  Game &game = Game::GetInstance();
  auto *renderer = game.GetRenderer();

  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = clipRect.w;
  dstrect.h = clipRect.h;

  SDL_RenderCopy(renderer, texture, &clipRect, &dstrect);
}

int Sprite::GetWidth() { return width; }

int Sprite::GetHeight() { return height; }

bool Sprite::IsOpen() { return texture != nullptr; }
