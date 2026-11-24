#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Building.h"

class BuildingManager {
private:
	std::vector<std::shared_ptr<Building>> buildings;
	int nextBuildingId = 1;

public:
	std::shared_ptr<Building> buildBuilding(const std::string& buildingType, int x = 0, int y = 0);
	std::shared_ptr<Building> getBuilding(int buildingId) const;
	std::shared_ptr<Building> getBuildingById(int buildingId) const;
	const std::vector<std::shared_ptr<Building>>& getBuildings() const;

	bool startResearch(int buildingId, const std::string& researchName);
	bool produceUnit(int buildingId, const std::string& unitType);

	std::shared_ptr<Building> getBuildingByType(const std::string& buildingType) const;
};