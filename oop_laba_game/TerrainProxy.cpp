#include "TerrainProxy.h"
#include <stdexcept>
#include <iostream>

TerrainProxy::TerrainProxy(std::shared_ptr<Terrain> terrain) : realTerrain(terrain) {
	if (!realTerrain) {
		throw std::invalid_argument("Terrain cant be null");
	}
}


bool TerrainProxy::isPassable(UnitType type) const {
	if (type == UnitType::JetpackUnit) {
		std::cout << "Летающий юнит может преодолеть любой ландшафт." << std::endl;
		return true;
	}

	bool passable = realTerrain->isPassable(type);

	std::cout << "Проверка проходимости ландшафта: "
		<< (passable ? "проходим" : "непроходим") << std::endl;

	return passable;
}

float TerrainProxy::getSpeedModifier(UnitType type) const {
	float modifier = realTerrain->getSpeedModifier(type);

	if (modifier < 0.0f || modifier > 1.0f) {
		throw std::runtime_error("Invalid terrain speed modifier");
	}

	std::cout << "Модификатор скорости юнита: " << modifier << std::endl;

	return modifier;
}

int TerrainProxy::getDefenseBonus(UnitType type) const {
	int bonus = realTerrain->getDefenseBonus(type);

	if (bonus < 0) {
		throw std::runtime_error("Invalid terrain defense bonus");
	}

	std::cout << "Бонус защиты ландшафта: " << bonus << std::endl;

	return bonus;
}

const Terrain* TerrainProxy::getRealTerrain() const {
	return realTerrain.get();
}