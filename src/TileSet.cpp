#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
    : tileSet(*new GameObject(), file) {
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;
  rows = tileSet.GetWidth() / tileWidth;
  columns = tileSet.GetHeight() / tileHeight;
}

void TileSet::RenderTile(int index, float x, float y) {
  // check if the index is valid
  if (index >= rows * columns) {
    return;
  }

  // calculate the tile's position
  int row = index / columns;
  int column = index % columns;

  // render the tile
  tileSet.Render(row, column);
}

int TileSet::GetTileWidth() { return tileWidth; }
int TileSet::GetTileHeight() { return tileHeight; }
