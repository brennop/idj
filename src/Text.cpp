#include "Text.h"
#include "Camera.h"
#include "Game.h"
#include "Resources.h"

Text::Text(GameObject &associated, std::string fontFile, int fontSize,
           TextStyle style, std::string text, SDL_Color color)
    : Component(associated), text(text), style(style), fontFile(fontFile),
      fontSize(fontSize), color(color) {
  font = Resources::GetFont(fontFile.c_str(), fontSize);
  RemakeTexture();
}

Text::~Text() { SDL_DestroyTexture(texture); }

void Text::Update(float dt) {}

void Text::Render() {
  SDL_Rect dstRect;
  // take camera into account
  dstRect.x = associated.box.x - Camera::pos.x;
  dstRect.y = associated.box.y - Camera::pos.y;
  dstRect.w = associated.box.w;
  dstRect.h = associated.box.h;
  SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, nullptr, &dstRect);
}

bool Text::Is(std::string type) { return type == "Text"; }

void Text::SetText(std::string text) {
  this->text = text;
  RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
  this->color = color;
  RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
  this->style = style;
  RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
  this->fontFile = fontFile;
  RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
  this->fontSize = fontSize;
  RemakeTexture();
}

void Text::RemakeTexture() {
  SDL_DestroyTexture(texture);
  font = Resources::GetFont(fontFile.c_str(), fontSize);
  switch (style) {
  case SOLID:
    texture = SDL_CreateTextureFromSurface(
        Game::GetInstance().GetRenderer(),
        TTF_RenderText_Solid(font, text.c_str(), color));
    break;
  case SHADED:
    texture = SDL_CreateTextureFromSurface(
        Game::GetInstance().GetRenderer(),
        TTF_RenderText_Shaded(font, text.c_str(), color, {0, 0, 0, 1}));
    break;
  case BLENDED:
    texture = SDL_CreateTextureFromSurface(
        Game::GetInstance().GetRenderer(),
        TTF_RenderText_Blended(font, text.c_str(), color));
    break;
  }
  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
  associated.box.w = w;
  associated.box.h = h;
}
