#include "UnitManager.h"
#include "Base.h"
#include "Unit.h"

UnitManager::UnitManager(Base* base) : base(base) {
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
		return false;
	}

	int dx = x - unit->getX();
	int dy = y - unit->getY();

	unit->move(dx, dy);

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