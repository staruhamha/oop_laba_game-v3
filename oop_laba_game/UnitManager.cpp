#include "UnitManager.h"
#include "Base.h"
#include "Unit.h"
#include "TerrainMap.h"
#include "Terrain.h"
#include <iostream>

UnitManager::UnitManager(Base* base) : base(base) {
}

void UnitManager::setTerrainMap(TerrainMap* terrainMap) {
	this->terrainMap = terrainMap;
}

std::shared_ptr<Unit> UnitManager::createUnit(int x, int y, const std::string& type) {
	if (base == nullptr) {
		return nullptr;
	}

	return base->createUnit(x, y, type);
}

std::shared_ptr<Unit> UnitManager::getUnit(int unitId) {
	if (base == nullptr) {
		return nullptr;
	}

	return base->getUnit(unitId);
}

bool UnitManager::moveUnit(int unitId, int x, int y) {
	std::shared_ptr<Unit> unit = getUnit(unitId);

	if (unit == nullptr) {
		std::cout << "Юнит не найден" << std::endl;
		return false;
	}

	if (terrainMap == nullptr) {
		std::cout << "Карта не подключена" << std::endl;
		return false;
	}

	if (x < 0 || y < 0 ||
		x >= terrainMap->getWidth() || y >= terrainMap->getHeight()) {
		std::cout << "Нельзя переместиться за пределы карты" << std::endl;
		return false;
	}

	Terrain* terrain = terrainMap->getTerrain(x, y);

	if (terrain == nullptr) {
		std::cout << "В этой клетке не задан ландшафт" << std::endl;
		return false;
	}

	UnitType type = unit->getTypeInfo().type;

	if (!terrain->isPassable(type)) {
		std::cout << "Юнит не может пройти через этот ландшафт" << std::endl;
		return false;
	}

	int dx = x - unit->getX();
	int dy = y - unit->getY();

	float speedModifier = terrain->getSpeedModifier(type);
	int defenseBonus = terrain->getDefenseBonus(type);

	unit->move(dx, dy);

	std::cout << "Юнит переместился на (" << x << ", " << y << ")" << std::endl;
	std::cout << "Модификатор скорости: " << speedModifier << std::endl;
	std::cout << "Бонус защиты: " << defenseBonus << std::endl;

	return true;
}

std::shared_ptr<Unit> UnitManager::getUnitById(int unitId) {
	return getUnit(unitId);
}

bool UnitManager::removeUnit(int unitId) {
	if (base == nullptr || getUnit(unitId) == nullptr) {
		return false;
	}

	base->removeUnit(unitId);
	return true;
}

bool UnitManager::isPositionValid(int x, int y) const {
	if (terrainMap == nullptr) {
		return false;
	}

	if (x < 0 || y < 0 ||
		x >= terrainMap->getWidth() || y >= terrainMap->getHeight()) {
		return false;
	}

	return terrainMap->getTerrain(x, y) != nullptr;
}

bool UnitManager::isPositionOccupied(int x, int y) const {
	if (base == nullptr) {
		return false;
	}

	for (const auto& unit : base->getUnits()) {
		if (unit != nullptr && unit->getX() == x && unit->getY() == y) {
			return true;
		}
	}

	return false;
}