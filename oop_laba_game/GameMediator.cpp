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
#include "UnitTypeInfo.h"

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
	lastOperationSucceeded = false;

	if (!unitManager) {
		return -1;
	}

	auto unit = unitManager->createUnit(x, y, type);

	if (!unit) {
		return -1;
	}

	lastOperationSucceeded = true;
	notifyUnitCreated();
	return unit->getId();
}

void GameMediator::moveUnit(int unitId, int x, int y) {
	lastOperationSucceeded = false;

	if (!unitManager) {
		return;
	}

	if (unitManager->moveUnit(unitId, x, y)) {
		lastOperationSucceeded = true;
	}
}
void GameMediator::attack(int attackerId, int targetId) {
	lastOperationSucceeded = false;

	if (!unitManager || !combatSystem) {
		return;
	}

	auto attacker = unitManager->getUnitById(attackerId);
	auto target = unitManager->getUnitById(targetId);

	if (!attacker || !target) {
		std::cout << "Юнит не найден." << std::endl;
		return;
	}

	combatSystem->attack(*attacker, *target);
	lastOperationSucceeded = true;
	notifyCombatResolved();
}

void GameMediator::resolveCombat(int attackerId, int targetId) {
	attack(attackerId, targetId);
}

void GameMediator::collectResource(int unitId, int resourcePointId) {
	lastOperationSucceeded = false;

	if (!unitManager || !materialsSystem) {
		return;
	}

	if (materialsSystem->collectResource(unitId, resourcePointId, 50, unitManager)) {
		lastOperationSucceeded = true;
		notifyResourceCollected();
	}
	else {
		std::cout << "Не удалось собрать ресурсы." << std::endl;
	}
}

void GameMediator::healUnit(int unitId, int targetId) {
	lastOperationSucceeded = false;

	if (!unitManager) {
		return;
	}

	auto unit = unitManager->getUnitById(unitId);
	auto target = unitManager->getUnitById(targetId);

	if (!unit || !target) {
		std::cout << "Юнит не найден." << std::endl;
		return;
	}

	target->restoreHealth(30);
	lastOperationSucceeded = true;

	std::cout << "Юнит восстановил здоровье цели." << std::endl;
}


void GameMediator::buildBuilding(const std::string& buildingType, int x, int y) {
	lastOperationSucceeded = false;
	if (buildingManager == nullptr || materialsSystem == nullptr ||
		base == nullptr || unitManager == nullptr) {
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

	if (!unitManager->isPositionValid(x, y)) {
		std::cout << "Недопустимые координаты строительства" << std::endl;
		return;
	}

	if (unitManager->isPositionOccupied(x, y)) {
		std::cout << "Клетка занята юнитом" << std::endl;
		return;
	}

	for (const auto& building : buildingManager->getBuildings()) {
		if (building != nullptr && building->getX() == x && building->getY() == y) {
			std::cout << "Клетка занята зданием" << std::endl;
			return;
		}
	}

	if (materialsSystem->getWood() < cost) {
		std::cout << "Недостаточно дерева для строительства" << std::endl;
		return;
	}

	std::shared_ptr<Building> building =
		buildingManager->buildBuilding(buildingType, x, y);

	if (building == nullptr) {
		std::cout << "Не удалось построить здание" << std::endl;
		return;
	}

	if (!materialsSystem->spendWood(cost)) {
		std::cout << "Не удалось списать ресурсы" << std::endl;
		return;
	}

	base->addBuilding(building);
	lastOperationSucceeded = true;
	std::cout << "Здание построено: " << buildingType << std::endl;
	notifyBuildingCompleted();
}


void GameMediator::startResearch(const std::string& technology) {
	lastOperationSucceeded = false;
	if (buildingManager == nullptr) {
		return;
	}

	std::string researchName;

	if (technology == "attack_upgrade") {
		researchName = "Улучшение оружия";
	}
	else if (technology == "defense_upgrade") {
		researchName = "Улучшение защиты";
	}
	else if (technology == "production_upgrade") {
		researchName = "Улучшение производства";
	}
	else {
		std::cout << "Неизвестная технология" << std::endl;
		return;
	}

	for (const auto& building : buildingManager->getBuildings()) {
		if (building != nullptr && building->getType() == "Laboratory") {
			if (buildingManager->startResearch(building->getId(), researchName)) {
				lastOperationSucceeded = true;
				notifyResearchCompleted();
			}
			return;
		}
	}

	std::cout << "Для исследования нужна лаборатория" << std::endl;
}

void GameMediator::distributeResources(const std::string& resourceType, int amount, int targetId) {
	lastOperationSucceeded = false;

	if (unitManager == nullptr || materialsSystem == nullptr) {
		return;
	}

	if (materialsSystem->distribute(resourceType, amount, targetId, unitManager)) {
		lastOperationSucceeded = true;
		std::cout << "Ресурсы переданы юниту с ID " << targetId << std::endl;
	}
	else {
		std::cout << "Не удалось передать ресурсы" << std::endl;
	}
}


void GameMediator::produceUnit(int buildingId, const std::string& unitType) {
	lastOperationSucceeded = false;

	if (unitManager == nullptr || buildingManager == nullptr ||
		materialsSystem == nullptr) {
		return;
	}

	std::shared_ptr<Building> building = buildingManager->getBuildingById(buildingId);

	if (building == nullptr || building->getType() != "Barracks") {
		std::cout << "Для производства нужна казарма" << std::endl;
		return;
	}

	UnitType type;
	std::string factoryType;

	if (unitType == "Infantry") {
		type = UnitType::Assault;
		factoryType = "Infantry";
	}
	else if (unitType == "Marksman") {
		type = UnitType::Marksman;
		factoryType = "Sniper";
	}
	else if (unitType == "Specialist") {
		type = UnitType::Specialist;
		factoryType = "Pyro";
	}
	else if (unitType == "JetpackUnit") {
		type = UnitType::JetpackUnit;
		factoryType = "JetpackTrooper";
	}
	else {
		std::cout << "Неизвестный тип юнита" << std::endl;
		return;
	}

	int cost = UnitTypeInfo::getInfo(type)->cost;

	if (materialsSystem->getWood() < cost) {
		std::cout << "Недостаточно дерева для производства" << std::endl;
		return;
	}

	int x = building->getX();
	int y = building->getY() + 1;

	if (!unitManager->isPositionValid(x, y) ||
		unitManager->isPositionOccupied(x, y)) {
		x = building->getX() + 1;
		y = building->getY();
	}

	if (!unitManager->isPositionValid(x, y) ||
		unitManager->isPositionOccupied(x, y)) {
		x = building->getX();
		y = building->getY() - 1;
	}

	if (!unitManager->isPositionValid(x, y) ||
		unitManager->isPositionOccupied(x, y)) {
		x = building->getX() - 1;
		y = building->getY();
	}

	if (!unitManager->isPositionValid(x, y) ||
		unitManager->isPositionOccupied(x, y)) {
		std::cout << "Нет свободной клетки для юнита" << std::endl;
		return;
	}

	std::shared_ptr<Unit> unit = unitManager->createUnit(x, y, factoryType);

	if (unit == nullptr) {
		std::cout << "Не удалось создать юнита" << std::endl;
		return;
	}

	if (!buildingManager->produceUnit(buildingId, unitType)) {
		unitManager->removeUnit(unit->getId());
		std::cout << "Не удалось произвести юнита" << std::endl;
		return;
	}

	materialsSystem->spendWood(cost);

	lastOperationSucceeded = true;
	notifyUnitCreated();

	std::cout << "Юнит произведён: " << unitType << std::endl;
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
	lastOperationSucceeded = false;

	if (buildingManager == nullptr || materialsSystem == nullptr) {
		return;
	}

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

	lastOperationSucceeded = true;
	std::cout << "Ресурсы переданы зданию " << buildingType << ": " << amount << "\n";
}

bool GameMediator::wasLastOperationSuccessful() const {
	return lastOperationSucceeded;
}

void GameMediator::resetOperationStatus() {
	lastOperationSucceeded = false;
}