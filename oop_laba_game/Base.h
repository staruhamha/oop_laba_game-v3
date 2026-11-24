#pragma once

#include <memory>
#include <vector>
#include "Unit.h"
#include "IObserver.h"
#include <string>

class Building;

class Base : public IObserver {
private:
	int health;
	int maxUnits;
	int unitCount;
	int defenseLevel;
	int resources;
	std::vector<std::shared_ptr<Unit>> units;
	std::vector<std::shared_ptr<Building>> buildings;

public:
	Base(int health, int maxUnits, int defenseLevel, int resources);

	Base(const Base& other) = delete;
	Base& operator=(const Base& other) = delete;
	Base(Base&& other) = delete;
	Base& operator=(Base&& other) = delete;

	int getHealth() const;
	int getMaxUnits() const;
	int getDefenseLevel() const;
	int getResources() const;
	int getUnitCount() const;
	void setHealth(int health);
	void setDefenseLevel(int defenseLevel);
	void addResources(int amount);

	void onUnitEvent(const UnitEvent& event) override;
	const std::vector<std::shared_ptr<Unit>>& getUnits() const;
	void addUnit(const std::shared_ptr<Unit>& unit);
	std::shared_ptr<Unit> createUnit(int x, int y, const std::string& type);
	std::shared_ptr<Unit> getUnit(int unitId) const;
	void removeUnit(int unitId);

	void addBuilding(const std::shared_ptr<Building>& building);
	std::shared_ptr<Building> getBuilding(int buildingId) const;
	int getBuildingCount() const;
	const std::vector<std::shared_ptr<Building>>& getBuildings() const;
};
