#include "TileMap.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "fallback_map.h"
#define TILEMAP_LOADER

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet)
    : Component(associated) {
  Load(file);
  this->tileSet = tileSet;
}

void TileMap::Load(std::string path) {
  std::ifstream file(path);

  // TODO: check error

  std::string line;
  getline(file, line, ',');
  mapWidth = stoi(line);
  getline(file, line, ',');
  mapHeight = stoi(line);
  getline(file, line, ',');
  mapDepth = stoi(line);

  while (getline(file, line)) {
    std::stringstream numbers(line);
    while (numbers.good()) {

      std::string number;
      getline(numbers, number, ',');

      if (number != "\r" && number != "\n") {
        tileMatrix.push_back(stoi(number) - 1);
      }
    }
  }
}

void TileMap::SetTileSet(TileSet *tileSet) { this->tileSet = tileSet; }

int &TileMap::At(int x, int y, int z) {
  return tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
  for (int i = 0; i < mapWidth; i++) {
    for (int j = 0; j < mapHeight; j++) {
      int tile = At(i, j, layer);
      tileSet->RenderTile(tile, i * tileSet->GetTileHeight(),
                          j * tileSet->GetTileWidth());
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
