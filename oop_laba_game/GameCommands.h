#pragma once

#include "Command.h"
#include <string>

class CreateUnitCommand : public Command {
private:
	std::string type;
	int x;
	int y;
	int unitId = -1;

public:
	CreateUnitCommand(std::shared_ptr<GameMediator> mediator, const std::string& type, int x, int y);
	void execute() override;
	int getUnitId() const;
};

class MoveUnitCommand : public Command {
private:
	int unitId;
	int x;
	int y;

public:
	MoveUnitCommand(std::shared_ptr<GameMediator> mediator, int unitId, int x, int y);
	void execute() override;
};

class AttackCommand : public Command {
private:
	int attackerId;
	int targetId;

public:
	AttackCommand(std::shared_ptr<GameMediator> mediator, int attackerId, int targetId);
	void execute() override;
};

class CollectResourceCommand : public Command {
private:
	int unitId;
	int resourcePointId;

public:
	CollectResourceCommand(std::shared_ptr<GameMediator> mediator, int unitId, int resourcePointId);
	void execute() override;
};

class HealCommand : public Command {
private:
	int unitId;
	int targetId;

public:
	HealCommand(std::shared_ptr<GameMediator> mediator, int unitId, int targetId);
	void execute() override;
};

class BuildBuildingCommand : public Command {
private:
	std::string buildingType;
	int x;
	int y;

public:
	BuildBuildingCommand(std::shared_ptr<GameMediator> mediator, const std::string& buildingType, int x, int y);
	void execute() override;
};

class ResearchCommand : public Command {
private:
	int technologyId;

public:
	ResearchCommand(std::shared_ptr<GameMediator> mediator, int technologyId);
	void execute() override;
};

class DistributeResourcesCommand : public Command {
private:
	std::string resourceType;
	int amount;
	std::string buildingType;

public:
	DistributeResourcesCommand(std::shared_ptr<GameMediator> mediator, const std::string& resourceType, int amount, const std::string& buildingType);
	void execute() override;
};

class ProduceUnitCommand : public Command {
private:
	int buildingId;
	std::string unitType;

public:
	ProduceUnitCommand(std::shared_ptr<GameMediator> mediator, int buildingId, const std::string& unitType);
	void execute() override;
};

class StatsCommand : public Command {
private:
	std::string parameter;

public:
	StatsCommand(std::shared_ptr<GameMediator> mediator, const std::string& parameter = "");
	void execute() override;
};