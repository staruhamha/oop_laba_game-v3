#include "Base.h"
#include "Factories.h"
#include <iostream>
#include "Building.h"

Base::Base(int health, int maxUnits, int defenseLevel, int resources) : health(health), maxUnits(maxUnits), unitCount(0), defenseLevel(defenseLevel), resources(resources) {
}


int Base::getHealth() const {
	return health;
}

int Base::getMaxUnits() const {
	return maxUnits;
}

int Base::getDefenseLevel() const {
	return defenseLevel;
}

int Base::getResources() const {
	return resources;
}

int Base::getUnitCount() const {
	return unitCount;
}


void Base::setHealth(int health) {
	this->health = health;
}

void Base::setDefenseLevel(int defenseLevel) {
	this->defenseLevel = defenseLevel;
}

void Base::addResources(int amount) {
	resources += amount;
}

const std::vector<std::shared_ptr<Unit>>& Base::getUnits() const {
	return units;
}

void Base::onUnitEvent(const UnitEvent& event) {
	switch (event.type) {
	case UnitEventType::Created:
		unitCount++;
		std::cout << "Юнит создан." << std::endl;
		break;

	case UnitEventType::Damaged:
		std::cout << "Юнит получил урон: " << event.damage << std::endl;
		break;

	case UnitEventType::Destroyed:
		if (unitCount > 0) {
			unitCount--;
		}
		std::cout << "Юнит устранён." << std::endl;
		break;
	}
}

void Base::addUnit(const std::shared_ptr<Unit>& unit) {
	if (unit != nullptr && unitCount < maxUnits) {
		units.push_back(unit);
		unit->subscribe(this);
		unit->notify(UnitEvent(UnitEventType::Created, unit->getId(), 0));
	}
}

std::shared_ptr<Unit> Base::createUnit(int x, int y, const std::string& type) {
	if (unitCount >= maxUnits) {
		return nullptr;
	}

	std::unique_ptr<Unit> newUnit;

	AssaultFactory assaultFactory;
	MarksmanFactory marksmanFactory;
	SpecialistFactory specialistFactory;
	JetpackFactory jetpackFactory;

	newUnit = assaultFactory.createUnit(x, y, type);

	if (newUnit == nullptr) {
		newUnit = marksmanFactory.createUnit(x, y, type);
	}

	if (newUnit == nullptr) {
		newUnit = specialistFactory.createUnit(x, y, type);
	}

	if (newUnit == nullptr) {
		newUnit = jetpackFactory.createUnit(x, y, type);
	}

	if (newUnit == nullptr) {
		return nullptr;
	}

	std::shared_ptr<Unit> unit = std::move(newUnit);
	addUnit(unit);

	return unit;
}

std::shared_ptr<Unit> Base::getUnit(int unitId) const {
	for (const auto& unit : units) {
		if (unit->getId() == unitId) {
			return unit;
		}
	}

	return nullptr;
}

void Base::removeUnit(int unitId) {
	for (auto it = units.begin(); it != units.end(); ++it) {
		if ((*it)->getId() == unitId) {
			(*it)->unsubscribe(this);
			units.erase(it);
			break;
		}
	}
}

void Base::addBuilding(const std::shared_ptr<Building>& building) {
	if (building != nullptr) {
		buildings.push_back(building);
	}
}

std::shared_ptr<Building> Base::getBuilding(int buildingId) const {
	for (const auto& building : buildings) {
		if (building->getId() == buildingId) {
			return building;
		}
	}

	return nullptr;
}

int Base::getBuildingCount() const {
	return static_cast<int>(buildings.size());
}

const std::vector<std::shared_ptr<Building>>& Base::getBuildings() const {
	return buildings;
}