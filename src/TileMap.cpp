#include "TileMap.h"

#include <cstdio>
#include <cstring>
#include <fstream>

#include "fallback_map.h"
#define TILEMAP_LOADER

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet)
    : Component(associated) {
  Load(file);
  this->tileSet = tileSet;
}

void TileMap::Load(std::string path) {

#ifdef TILEMAP_LOADER
  std::ifstream file(path);

  // TODO: check error

  std::string line;

  printf("carregando mapa...");

  getline(file, line, ',');
  mapWidth = stoi(line);
  getline(file, line, ',');
  mapHeight = stoi(line);
  getline(file, line, ',');
  mapDepth = stoi(line);

  tileMatrix = std::vector<int>(mapWidth * mapHeight * mapDepth);

  while (getline(file, line, ',')) {
    if (strncmp(line.c_str(), "\n", 1) == 0 &&
        strncmp(line.c_str(), "\r", 1) == 0) {
      tileMatrix.push_back(stoi(line) - 1);
    }
  }
#else
  mapWidth = 25;
  mapHeight = 25;
  mapDepth = 2;

  tileMatrix = std::vector<int>(mapWidth * mapHeight * mapDepth);

  for (int i = 0; i < 1250; i++) {
    tileMatrix[i] = fallback_map[i];
  }
#endif
}

void TileMap::SetTileSet(TileSet *tileSet) { this->tileSet = tileSet; }

int &TileMap::At(int x, int y, int z) {
  return tileMatrix[z + x * mapWidth + y * mapWidth * mapHeight];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
  for (int i = 0; i < mapWidth; i++) {
    for (int j = 0; j < mapHeight; j++) {
      int tile = At(i, j, layer);
      tileSet->RenderTile(tile, i * tileSet->GetTileWidth(),
                          j * tileSet->GetTileHeight());
    }
  }
}

void TileMap::Render() {
  for (int i = 0; i < mapDepth; i++) {
    RenderLayer(i, 0, 0);
  }
}

void TileMap::Update(float dt) {}
bool TileMap::Is(std::string type) { return type == "TileMap"; }

int TileMap::GetWidth() { return mapWidth; }
int TileMap::GetHeight() { return mapHeight; }
int TileMap::GetDepth() { return mapDepth; }
