#pragma once

#include "Wood.h"
#include "Metal.h"
#include "Energy.h"
#include "ResourcePoint.h"

#include <string>
#include <vector>
#include <memory>

class UnitManager;

class MaterialsSystem {
private:
	Wood wood;
	Metal metal;
	Energy energy;
	std::vector<std::shared_ptr<ResourcePoint>> resourcePoints;
	int nextResourcePointId = 1;

public:
	MaterialsSystem(int woodAmount, int metalAmount, int energyAmount);

	void addResourcePoint(const std::string& resourceType, int amount);
	bool collectResource(int unitId, int resourcePointId, int amount, UnitManager* unitManager);

	void addWood(int amount);
	void addMetal(int amount);
	void addEnergy(int amount);

	bool spendWood(int amount);
	bool spendMetal(int amount);
	bool spendEnergy(int amount);

	void addResources(const std::string& resourceType, int amount);
	bool spendResources(const std::string& resourceType, int amount);
	bool distribute(const std::string& resourceType, int amount, int unitId, UnitManager* unitManager);

	int getWood() const;
	int getMetal() const;
	int getEnergy() const;
};