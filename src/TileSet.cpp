#include "TileSet.h"
#include <cstdio>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
    : tileSet(*new GameObject(), file) {
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;
  columns = tileSet.GetWidth() / tileWidth;
  rows = tileSet.GetHeight() / tileHeight;
}

void TileSet::RenderTile(int index, float x, float y) {
  // check if the index is valid
  if (index >= rows * columns) {
    return;
  }

  // calculate the tile's position
  int row = index / columns;
  int column = index % columns;

  tileSet.SetClip(row * tileHeight, column * tileWidth, tileWidth, tileHeight);

  // render the tile
  tileSet.Render(x, y);
}

int TileSet::GetTileWidth() { return tileWidth; }
int TileSet::GetTileHeight() { return tileHeight; }
