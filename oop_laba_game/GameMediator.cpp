#include "GameMediator.h"
#include "UnitManager.h"
#include "CombatSystem.h"
#include "Unit.h"
#include "MaterialsSystem.h"
#include "BuildingManager.h"
#include "Base.h"
#include "Building.h"
#include "Health.h"
#include <iostream>

GameMediator::GameMediator(
	Base* base,
	UnitManager* unitManager,
	MaterialsSystem* materialsSystem,
	CombatSystem* combatSystem,
	BuildingManager* buildingManager
) : base(base), unitManager(unitManager), materialsSystem(materialsSystem),
combatSystem(combatSystem), buildingManager(buildingManager) {
}

int GameMediator::createUnit(const std::string& type, int x, int y) {
	if (unitManager == nullptr) {
		return -1;
	}

	std::shared_ptr<Unit> unit = unitManager->createUnit(x, y, type);

	if (unit == nullptr) {
		return -1;
	}

	notifyUnitCreated();

	return unit->getId();
}

void GameMediator::moveUnit(int unitId, int x, int y) {
	if (unitManager == nullptr) {
		return;
	}

	unitManager->moveUnit(unitId, x, y);
}

void GameMediator::attack(int attackerId, int targetId) {
	if (unitManager == nullptr || combatSystem == nullptr) {
		return;
	}

	std::shared_ptr<Unit> attacker = unitManager->getUnit(attackerId);
	std::shared_ptr<Unit> target = unitManager->getUnit(targetId);

	if (attacker == nullptr || target == nullptr) {
		return;
	}

	combatSystem->attack(*attacker, *target);
	notifyCombatResolved();
}

void GameMediator::resolveCombat(int attackerId, int targetId) {
	attack(attackerId, targetId);
}

void GameMediator::collectResource(int unitId, int resourcePointId) {
	if (unitManager == nullptr || materialsSystem == nullptr) {
		return;
	}

	if (materialsSystem->collectResource(unitId, resourcePointId, 50, unitManager)) {
		notifyResourceCollected();
	}
	else {
		std::cout << "Не удалось собрать ресурсы" << std::endl;
	}
}

void GameMediator::healUnit(int unitId, int targetId) {
	if (unitManager == nullptr) {
		return;
	}

	std::shared_ptr<Unit> unit = unitManager->getUnit(unitId);
	std::shared_ptr<Unit> target = unitManager->getUnit(targetId);

	if (unit == nullptr || target == nullptr) {
		std::cout << "Юнит не найден" << std::endl;
		return;
	}

	target->restoreHealth(30);

	std::cout << "Юнит восстановил здоровье другому юниту" << std::endl;
}


void GameMediator::buildBuilding(const std::string& buildingType, int x, int y) {
	if (buildingManager == nullptr || materialsSystem == nullptr || base == nullptr) {
		return;
	}

	int cost = 0;

	if (buildingType == "Barracks") {
		cost = 200;
	}
	else if (buildingType == "PowerPlant") {
		cost = 150;
	}
	else if (buildingType == "Laboratory") {
		cost = 250;
	}
	else if (buildingType == "Warehouse") {
		cost = 100;
	}
	else if (buildingType == "Hospital") {
		cost = 180;
	}
	else {
		std::cout << "Неизвестный тип здания" << std::endl;
		return;
	}

	if (!materialsSystem->spendWood(cost)) {
		std::cout << "Недостаточно дерева для строительства" << std::endl;
		return;
	}

	std::shared_ptr<Building> building = buildingManager->buildBuilding(buildingType, x, y);

	if (building == nullptr) {
		return;
	}

	base->addBuilding(building);

	std::cout << "Здание построено: " << buildingType << std::endl;
	notifyBuildingCompleted();
}


void GameMediator::startResearch(int technologyId) {
	if (buildingManager == nullptr) {
		return;
	}

	std::string researchName;

	switch (technologyId) {
	case 1:
		researchName = "Улучшение оружия";
		break;
	case 2:
		researchName = "Улучшение защиты";
		break;
	case 3:
		researchName = "Улучшение производства";
		break;
	default:
		std::cout << "Неизвестная технология" << std::endl;
		return;
	}

	for (const auto& building : buildingManager->getBuildings()) {
		if (building != nullptr && building->getType() == "Laboratory") {
			if (buildingManager->startResearch(building->getId(), researchName)) {
				notifyResearchCompleted();
			}
			return;
		}
	}

	std::cout << "Для исследования нужна лаборатория" << std::endl;
}

void GameMediator::distributeResources(const std::string& resourceType, int amount, int targetId) {
	if (unitManager == nullptr || materialsSystem == nullptr) {
		return;
	}

	if (materialsSystem->distribute(resourceType, amount, targetId, unitManager)) {
		std::cout << "Ресурсы переданы юниту с ID " << targetId << std::endl;
	}
	else {
		std::cout << "Не удалось передать ресурсы" << std::endl;
	}
}


void GameMediator::produceUnit(int buildingId, const std::string& unitType) {
	if (unitManager == nullptr || buildingManager == nullptr) {
		return;
	}

	std::shared_ptr<Building> building = buildingManager->getBuildingById(buildingId);

	if (building == nullptr) {
		std::cout << "Указанное здание не найдено" << std::endl;
		return;
	}

	if (buildingManager->produceUnit(buildingId, unitType)) {
		if (unitManager->createUnit(0, 0, unitType) != nullptr) {
			notifyUnitCreated();
		}
	}
	else {
		std::cout << "Не удалось произвести юнита" << std::endl;
	}
}

void GameMediator::getStats(const std::string& parameter) {
	if (base == nullptr || materialsSystem == nullptr || buildingManager == nullptr) {
		return;
	}

	if (parameter.empty() || parameter == "units") {
		std::cout << "Здоровье базы: " << base->getHealth() << std::endl;
		std::cout << "Количество юнитов: " << base->getUnitCount() << std::endl;

		for (const auto& unit : base->getUnits()) {
			std::cout << "\nЮнит ID: " << unit->getId() << std::endl;
			std::cout << "Позиция: " << unit->getX() << ", " << unit->getY() << std::endl;
		}
	}

	if (parameter.empty() || parameter == "buildings") {
		std::cout << "\nКоличество зданий: "
			<< buildingManager->getBuildings().size() << std::endl;

		for (const auto& building : buildingManager->getBuildings()) {
			std::cout << "\nЗдание: " << building->getType() << std::endl;
			std::cout << "ID: " << building->getId() << std::endl;
			std::cout << "Позиция: " << building->getX() << ", " << building->getY() << std::endl;
			std::cout << "Дерево в здании: " << building->getWood() << std::endl;
		}
	}

	if (parameter.empty() || parameter == "resources") {
		std::cout << "\nРесурсы базы: " << base->getResources() << std::endl;
		std::cout << "Дерево: " << materialsSystem->getWood() << std::endl;
		std::cout << "Металл: " << materialsSystem->getMetal() << std::endl;
		std::cout << "Энергия: " << materialsSystem->getEnergy() << std::endl;
	}
}

void GameMediator::notifyUnitCreated() {
	std::cout << "Юнит создан" << std::endl;
}

void GameMediator::notifyResourceCollected() {
	std::cout << "Ресурсы собраны" << std::endl;
}

void GameMediator::notifyCombatResolved() {
	std::cout << "Бой завершён" << std::endl;
}

void GameMediator::notifyBuildingCompleted() {
	std::cout << "Строительство завершено" << std::endl;
}

void GameMediator::notifyResearchCompleted() {
	std::cout << "Уведомление: исследование завершено" << std::endl;
}

void GameMediator::distributeResources(const std::string& resourceType, int amount, const std::string& buildingType) {
	if (amount <= 0) {
		std::cout << "Количество ресурсов должно быть положительным\n";
		return;
	}

	auto building = buildingManager->getBuildingByType(buildingType);

	if (!building) {
		std::cout << "Здание не найдено\n";
		return;
	}

	std::string resource = resourceType;

	if (resource == "wood" || resource == "Wood") {
		resource = "Wood";
	}
	else if (resource == "metal" || resource == "Metal") {
		resource = "Metal";
	}
	else if (resource == "energy" || resource == "Energy") {
		resource = "Energy";
	}
	else {
		std::cout << "Неизвестный тип ресурса\n";
		return;
	}

	if (!materialsSystem->spendResources(resource, amount)) {
		std::cout << "Недостаточно ресурсов\n";
		return;
	}

	if (resource == "Wood") {
		building->addWood(amount);
	}

	std::cout << "Ресурсы переданы зданию " << buildingType << ": " << amount << "\n";
}