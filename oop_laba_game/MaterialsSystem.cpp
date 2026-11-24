#include "MaterialsSystem.h"
#include "UnitManager.h"
#include "Unit.h"

MaterialsSystem::MaterialsSystem(int woodAmount, int metalAmount, int energyAmount)
	: wood(woodAmount), metal(metalAmount), energy(energyAmount) {
}

void MaterialsSystem::addResourcePoint(const std::string& resourceType, int amount) {
	if (amount <= 0) {
		return;
	}

	if (resourceType != "Wood" && resourceType != "Metal" && resourceType != "Energy") {
		return;
	}

	auto point = std::make_shared<ResourcePoint>(
		nextResourcePointId,
		resourceType,
		amount
	);

	resourcePoints.push_back(point);
	nextResourcePointId++;
}

bool MaterialsSystem::collectResource(int unitId, int resourcePointId, int amount, UnitManager* unitManager) {
	if (unitManager == nullptr || amount <= 0) {
		return false;
	}

	if (unitManager->getUnit(unitId) == nullptr) {
		return false;
	}

	for (const auto& point : resourcePoints) {
		if (point != nullptr && point->getId() == resourcePointId) {
			int collected = point->collect(amount);

			if (collected <= 0) {
				return false;
			}

			addResources(point->getResourceType(), collected);
			return true;
		}
	}

	return false;
}

void MaterialsSystem::addWood(int amount) {
	wood.increase(amount);
}

void MaterialsSystem::addMetal(int amount) {
	metal.increase(amount);
}

void MaterialsSystem::addEnergy(int amount) {
	energy.increase(amount);
}

bool MaterialsSystem::spendWood(int amount) {
	if (wood.getAmount() < amount) {
		return false;
	}

	wood.decrease(amount);
	return true;
}

bool MaterialsSystem::spendMetal(int amount) {
	if (metal.getAmount() < amount) {
		return false;
	}

	metal.decrease(amount);
	return true;
}

bool MaterialsSystem::spendEnergy(int amount) {
	if (energy.getAmount() < amount) {
		return false;
	}

	energy.decrease(amount);
	return true;
}

int MaterialsSystem::getWood() const {
	return wood.getAmount();
}

int MaterialsSystem::getMetal() const {
	return metal.getAmount();
}

int MaterialsSystem::getEnergy() const {
	return energy.getAmount();
}

void MaterialsSystem::addResources(const std::string& resourceType, int amount) {
	if (amount <= 0) {
		return;
	}

	if (resourceType == "Wood") {
		addWood(amount);
	}
	else if (resourceType == "Metal") {
		addMetal(amount);
	}
	else if (resourceType == "Energy") {
		addEnergy(amount);
	}
}

bool MaterialsSystem::spendResources(const std::string& resourceType, int amount) {
	if (amount <= 0) {
		return false;
	}

	if (resourceType == "Wood") {
		return spendWood(amount);
	}
	else if (resourceType == "Metal") {
		return spendMetal(amount);
	}
	else if (resourceType == "Energy") {
		return spendEnergy(amount);
	}

	return false;
}

bool MaterialsSystem::distribute(const std::string& resourceType, int amount, int unitId, UnitManager* unitManager) {
	if (unitManager == nullptr || amount <= 0) {
		return false;
	}

	std::shared_ptr<Unit> unit = unitManager->getUnit(unitId);

	if (unit == nullptr || !spendResources(resourceType, amount)) {
		return false;
	}

	if (resourceType == "Wood") {
		unit->addWood(amount);
	}
	else if (resourceType == "Metal") {
		unit->addMetal(amount);
	}
	else if (resourceType == "Energy") {
		unit->addEnergy(amount);
	}
	else {
		return false;
	}

	return true;
}