#include "TerrainMap.h"
#include "TerrainProxy.h"
#include "TerrainTypes.h"
#include <iostream>
#include <windows.h>

TerrainMap::TerrainMap(int width, int height) {
	map.resize(height);
	neutralObjects.resize(height);

	for (int y = 0; y < height; y++) {
		map[y].resize(width);
		neutralObjects[y].resize(width);
	}
}


Terrain* TerrainMap::getTerrain(int x, int y) const {
	if (x < 0 || y < 0 || y >= map.size() || x >= map[y].size()) {
		return nullptr;
	}

	return map[y][x].get();
}


void TerrainMap::setTerrain(int x, int y, std::unique_ptr<Terrain> terrain) {
	if (x >= 0 && y >= 0 && y < map.size() && x < map[y].size()) {
		if (terrain == nullptr) {
			map[y][x].reset();
			return;
		}

		std::shared_ptr<Terrain> realTerrain = std::move(terrain);
		map[y][x] = std::make_unique<TerrainProxy>(realTerrain);
	}
}

NeutralObject* TerrainMap::getNeutralObjectAt(int x, int y) const {
	if (x < 0 || y < 0 || y >= neutralObjects.size() || x >= neutralObjects[y].size()) {
		return nullptr;
	}

	return neutralObjects[y][x].get();
}


void TerrainMap::setNeutralObjectAt(int x, int y, std::shared_ptr<NeutralObject> object) {
	if (x >= 0 && y >= 0 && y < neutralObjects.size() && x < neutralObjects[y].size()) {
		neutralObjects[y][x] = object;
	}
}

int TerrainMap::getWidth() const {
	if (map.empty()) {
		return 0;
	}

	return static_cast<int>(map[0].size());
}


int TerrainMap::getHeight() const {
	return static_cast<int>(map.size());
}

