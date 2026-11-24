#include "GameFacade.h"
#include "Command.h"
#include "GameCommands.h"
#include "GameMediator.h"
#include "GameHandlers.h"
#include "Base.h"
#include "UnitManager.h"
#include "MaterialsSystem.h"
#include "CombatSystem.h"
#include "BuildingManager.h"

GameFacade::GameFacade() {
	base = std::make_unique<Base>(1000, 5, 0, 100);
	unitManager = std::make_unique<UnitManager>(base.get());
	materialsSystem = std::make_unique<MaterialsSystem>(1000, 100, 100);

	materialsSystem->addResourcePoint("Wood", 200);
	materialsSystem->addResourcePoint("Metal", 150);
	materialsSystem->addResourcePoint("Energy", 100);

	combatSystem = std::make_unique<CombatSystem>();
	buildingManager = std::make_unique<BuildingManager>();

	mediator = std::make_shared<GameMediator>(
		base.get(),
		unitManager.get(),
		materialsSystem.get(),
		combatSystem.get(),
		buildingManager.get()
	);

	commandHistory = std::make_shared<CommandHistory>();

	auto createHandler = std::make_shared<CreateHandler>(this);
	auto moveHandler = std::make_shared<MoveHandler>(this);
	auto attackHandler = std::make_shared<AttackHandler>(this);
	auto collectHandler = std::make_shared<CollectHandler>(this);
	auto healHandler = std::make_shared<HealHandler>(this);
	auto buildHandler = std::make_shared<BuildHandler>(this);
	auto researchHandler = std::make_shared<ResearchHandler>(this);
	auto produceHandler = std::make_shared<ProduceHandler>(this);
	auto statsHandler = std::make_shared<StatsHandler>(this);
	auto distributeHandler = std::make_shared<DistributeHandler>(this);

	createHandler->setNext(moveHandler);
	moveHandler->setNext(attackHandler);
	attackHandler->setNext(collectHandler);
	collectHandler->setNext(distributeHandler);
	distributeHandler->setNext(healHandler);
	healHandler->setNext(buildHandler);
	buildHandler->setNext(researchHandler);
	researchHandler->setNext(produceHandler);
	produceHandler->setNext(statsHandler);

	handler = createHandler;
}

GameFacade::~GameFacade() = default;

int GameFacade::createUnit(const std::string& type, int x, int y) {
	auto command = std::make_shared<CreateUnitCommand>(mediator, type, x, y);
	executeCommand(command);

	return command->getUnitId();
}

void GameFacade::moveUnit(int unitId, int x, int y) {
	auto command = std::make_shared<MoveUnitCommand>(mediator, unitId, x, y);
	executeCommand(command);
}

void GameFacade::attack(int attackerId, int targetId) {
	auto command = std::make_shared<AttackCommand>(mediator, attackerId, targetId);
	executeCommand(command);
}

void GameFacade::collectResource(int unitId, int resourcePointId) {
	auto command = std::make_shared<CollectResourceCommand>(mediator, unitId, resourcePointId);
	executeCommand(command);
}

void GameFacade::heal(int unitId, int targetId) {
	auto command = std::make_shared<HealCommand>(mediator, unitId, targetId);
	executeCommand(command);
}

void GameFacade::buildBuilding(const std::string& buildingType, int x, int y) {
	auto command = std::make_shared<BuildBuildingCommand>(mediator, buildingType, x, y);
	executeCommand(command);
}

void GameFacade::research(int technologyId) {
	auto command = std::make_shared<ResearchCommand>(mediator, technologyId);
	executeCommand(command);
}

void GameFacade::distributeResources(const std::string& resourceType, int amount, const std::string& buildingType) {
	auto command = std::make_shared<DistributeResourcesCommand>(mediator, resourceType, amount, buildingType);
	executeCommand(command);
}

void GameFacade::produceUnit(int buildingId, const std::string& unitType) {
	auto command = std::make_shared<ProduceUnitCommand>(mediator, buildingId, unitType);
	executeCommand(command);
}

void GameFacade::getStats(const std::string& parameter) {
	auto command = std::make_shared<StatsCommand>(mediator, parameter);
	executeCommand(command);
}

void GameFacade::executeCommand(std::shared_ptr<Command> command) {
	if (command) {
		command->execute();
		commandHistory->push(command);
	}
}

bool GameFacade::processInput(const std::string& input) {
	if (handler) {
		return handler->handle(input);
	}

	return false;
}

Base* GameFacade::getBase() const {
	return base.get();
}