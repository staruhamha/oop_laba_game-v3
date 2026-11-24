#pragma once
#include <string>

class Base;
class UnitManager;
class MaterialsSystem;
class CombatSystem;
class BuildingManager;

class GameMediator {
private:
	Base* base;
	UnitManager* unitManager;
	MaterialsSystem* materialsSystem;
	CombatSystem* combatSystem;
	BuildingManager* buildingManager;

public:
	GameMediator(
		Base* base,
		UnitManager* unitManager,
		MaterialsSystem* materialsSystem,
		CombatSystem* combatSystem,
		BuildingManager* buildingManager
	);

	int createUnit(const std::string& type, int x, int y);
	void moveUnit(int unitId, int x, int y);
	void attack(int attackerId, int targetId);
	void collectResource(int unitId, int resourcePointId);
	void healUnit(int unitId, int targetId);
	void resolveCombat(int attackerId, int targetId);
	void buildBuilding(const std::string& buildingType, int x, int y);
	void startResearch(int technologyId);
	void distributeResources(const std::string& resourceType, int amount, int targetId);
	void distributeResources(const std::string& resourceType, int amount, const std::string& buildingType);
	void produceUnit(int buildingId, const std::string& unitType);

	void getStats(const std::string& parameter = "");

	void notifyUnitCreated();
	void notifyResourceCollected();
	void notifyCombatResolved();
	void notifyBuildingCompleted();
	void notifyResearchCompleted();
};