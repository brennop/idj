#ifndef __TILE_SET_H__
#define __TILE_SET_H__

#include <string>

#include <Sprite.h>

class TileSet {
public:
  TileSet(int tileWidth, int tileHeight, std::string file);
  void RenderTile(int index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();

private:
  Sprite tileSet;
  int tileWidth;
  int tileHeight;
  int rows;
  int columns;
};

#endif // __TILE_SET_H__
