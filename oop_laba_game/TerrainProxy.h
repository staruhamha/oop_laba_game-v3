#pragma once

#include "Terrain.h"
#include <memory>

class TerrainProxy : public Terrain {
private:
	std::shared_ptr<Terrain> realTerrain;

public:
	TerrainProxy(std::shared_ptr<Terrain> terrain);

	bool isPassable(UnitType type) const override;
	float getSpeedModifier(UnitType type) const override;
	int getDefenseBonus(UnitType type) const override;

	const Terrain* getRealTerrain() const;
};