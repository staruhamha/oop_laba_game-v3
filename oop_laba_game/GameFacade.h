#pragma once

#include <memory>
#include <string>
#include "CommandHistory.h"
#include <vector>

class GameMediator;
class Handler;
class Command;
class Base;
class UnitManager;
class MaterialsSystem;
class CombatSystem;
class BuildingManager;
class TerrainMap;
class GameController;

class GameFacade {
private:
	std::shared_ptr<GameController> gameController;
	std::unique_ptr<UnitManager> unitManager;
	std::unique_ptr<MaterialsSystem> materialsSystem;
	std::unique_ptr<CombatSystem> combatSystem;
	std::unique_ptr<BuildingManager> buildingManager;
	std::shared_ptr<CommandHistory> commandHistory;
	std::shared_ptr<GameMediator> mediator;
	std::shared_ptr<Handler> handler;
	std::vector<std::string> commandLog;
public:
	
	~GameFacade();
	GameFacade(std::shared_ptr<GameController> gameController);
	int createUnit(const std::string& type, int x, int y);
	void moveUnit(int unitId, int x, int y);
	void attack(int attackerId, int targetId);
	void collectResource(int unitId, int resourcePointId);
	void heal(int unitId, int targetId);

	void buildBuilding(const std::string& buildingType, int x, int y);
	void research(const std::string& technology);
	void distributeResources(const std::string& resourceType, int amount, const std::string& buildingType);
	void produceUnit(int buildingId, const std::string& unitType);
	Base* getBase() const;
	void getStats(const std::string& parameter = "");
	
	void executeCommand(std::shared_ptr<Command> command);
	bool processInput(const std::string& input);
	void setTerrainMap(TerrainMap* terrainMap);

	void showCommandLog() const;
};