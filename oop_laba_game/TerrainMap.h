#pragma once

#include <vector>
#include <memory>
#include "Terrain.h"
#include "NeutralObjects.h"

class TerrainMap {
private:
	std::vector<std::vector<std::unique_ptr<Terrain>>> map;
	std::vector<std::vector<std::shared_ptr<NeutralObject>>> neutralObjects;

public:
	TerrainMap(int width, int height);

	TerrainMap(const TerrainMap& other) = delete;
	TerrainMap& operator=(const TerrainMap& other) = delete;
	TerrainMap(TerrainMap&& other) noexcept = default;
	TerrainMap& operator=(TerrainMap&& other) noexcept = default;

	Terrain* getTerrain(int x, int y) const;
	void setTerrain(int x, int y, std::unique_ptr<Terrain> terrain);
	NeutralObject* getNeutralObjectAt(int x, int y) const;
	void setNeutralObjectAt(int x, int y, std::shared_ptr<NeutralObject> object);
	int getWidth() const;
	int getHeight() const;

	
};