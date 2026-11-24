#include "BuildingManager.h"
#include "Buildings.h"

#include <iostream>
#include <utility>

using namespace std;

shared_ptr<Building> BuildingManager::buildBuilding(const string& buildingType, int x, int y) {
	shared_ptr<Building> building;

	if (buildingType == "Barracks") {
		building = make_shared<Barracks>(nextBuildingId, x, y);
	}
	else if (buildingType == "PowerPlant") {
		building = make_shared<PowerPlant>(nextBuildingId, x, y);
	}
	else if (buildingType == "Laboratory") {
		building = make_shared<Laboratory>(nextBuildingId, x, y);
	}
	else if (buildingType == "Warehouse") {
		building = make_shared<Warehouse>(nextBuildingId, x, y);
	}
	else if (buildingType == "Hospital") {
		building = make_shared<Hospital>(nextBuildingId, x, y);
	}
	else {
		return nullptr;
	}

	building->completeConstruction();
	buildings.push_back(building);
	nextBuildingId++;

	return building;
}

shared_ptr<Building> BuildingManager::getBuilding(int buildingId) const {
	for (const auto& building : buildings) {
		if (building->getId() == buildingId) {
			return building;
		}
	}

	return nullptr;
}

const vector<shared_ptr<Building>>& BuildingManager::getBuildings() const {
	return buildings;
}

shared_ptr<Building> BuildingManager::getBuildingById(int buildingId) const {
	return getBuilding(buildingId);
}

bool BuildingManager::startResearch(int buildingId, const string& researchName) {
	shared_ptr<Building> building = getBuildingById(buildingId);

	if (building == nullptr || building->getName() != "Laboratory" || researchName.empty()) {
		return false;
	}

	cout << "Начато исследование: " << researchName << endl;
	return true;
}

bool BuildingManager::produceUnit(int buildingId, const string& unitType) {
	shared_ptr<Building> building = getBuildingById(buildingId);

	if (building == nullptr || building->getName() != "Barracks" || unitType.empty()) {
		return false;
	}

	building->produce(unitType);
	return true;
}

std::shared_ptr<Building> BuildingManager::getBuildingByType(const std::string& buildingType) const {
	for (const auto& building : buildings) {
		if (building->getType() == buildingType) {
			return building;
		}
	}

	return nullptr;
}