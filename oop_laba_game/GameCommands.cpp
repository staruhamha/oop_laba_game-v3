#include "GameCommands.h"
#include "GameMediator.h"

CreateUnitCommand::CreateUnitCommand(std::shared_ptr<GameMediator> mediator, const std::string& type, int x, int y) : Command(mediator), type(type), x(x), y(y) {
}

void CreateUnitCommand::execute() {
	if (!isValid()) {
		return;
	}

	unitId = mediator->createUnit(type, x, y);
}

int CreateUnitCommand::getUnitId() const {
	return unitId;
}

MoveUnitCommand::MoveUnitCommand(std::shared_ptr<GameMediator> mediator, int unitId, int x, int y) : Command(mediator), unitId(unitId), x(x), y(y) {
}

void MoveUnitCommand::execute() {
	if (!isValid()) {
		return;
	}

	mediator->moveUnit(unitId, x, y);
}

AttackCommand::AttackCommand(std::shared_ptr<GameMediator> mediator, int attackerId, int targetId) : Command(mediator), attackerId(attackerId), targetId(targetId) {
}

void AttackCommand::execute() {
	if (!isValid()) {
		return;
	}

	mediator->resolveCombat(attackerId, targetId);
}

CollectResourceCommand::CollectResourceCommand(std::shared_ptr<GameMediator> mediator, int unitId, int resourcePointId) : Command(mediator), unitId(unitId), resourcePointId(resourcePointId) {
}

void CollectResourceCommand::execute() {
	if (!isValid()) {
		return;
	}

	mediator->collectResource(unitId, resourcePointId);
}

HealCommand::HealCommand(std::shared_ptr<GameMediator> mediator, int unitId, int targetId) : Command(mediator), unitId(unitId), targetId(targetId) {
}

void HealCommand::execute() {
	if (!isValid()) {
		return;
	}

	mediator->healUnit(unitId, targetId);
}

BuildBuildingCommand::BuildBuildingCommand(std::shared_ptr<GameMediator> mediator, const std::string& buildingType, int x, int y) : Command(mediator), buildingType(buildingType), x(x), y(y) {
}

void BuildBuildingCommand::execute() {
	if (!isValid()) {
		return;
	}

	mediator->buildBuilding(buildingType, x, y);
}

ResearchCommand::ResearchCommand(std::shared_ptr<GameMediator> mediator, const std::string& technology) : Command(mediator), technology(technology) {
}

void ResearchCommand::execute() {
	if (!isValid()) {
		return;
	}

	mediator->startResearch(technology);
}

DistributeResourcesCommand::DistributeResourcesCommand(std::shared_ptr<GameMediator> mediator, const std::string& resourceType, int amount, const std::string& buildingType) : Command(mediator), resourceType(resourceType), amount(amount), buildingType(buildingType) {
}

void DistributeResourcesCommand::execute() {
	if (isValid()) {
		mediator->distributeResources(resourceType, amount, buildingType);
	}
}

ProduceUnitCommand::ProduceUnitCommand(std::shared_ptr<GameMediator> mediator, int buildingId, const std::string& unitType) : Command(mediator), buildingId(buildingId), unitType(unitType) {
}

void ProduceUnitCommand::execute() {
	if (!isValid()) {
		return;
	}

	mediator->produceUnit(buildingId, unitType);
}

StatsCommand::StatsCommand(std::shared_ptr<GameMediator> mediator, const std::string& parameter)
	: Command(mediator), parameter(parameter) {
}

void StatsCommand::execute() {
	if (isValid()) {
		mediator->getStats(parameter);
	}
}