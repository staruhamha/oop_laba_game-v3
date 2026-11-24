
#include "GameHandlers.h"
#include "GameFacade.h"

#include <sstream>

CreateHandler::CreateHandler(GameFacade* facade) : facade(facade) {
}

bool CreateHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string unit;
	std::string type;
	std::string at;
	std::string coordinates;
	int x, y;
	char comma;

	stream >> command;

	if (command == "create" &&
		stream >> unit >> type >> at >> coordinates &&
		unit == "unit" && at == "at") {

		std::istringstream coordinateStream(coordinates);

		if (!(coordinateStream >> x >> comma >> y) || comma != ',') {
			return false;
		}

		if (facade == nullptr) {
			return false;
		}

		if (type == "infantry") {
			type = "Infantry";
		}
		else if (type == "scout") {
			type = "Scout";
		}

		facade->createUnit(type, x, y);
		return true;
	}

	if (next_) {
		return next_->handle(cmd);
	}

	return false;
}

MoveHandler::MoveHandler(GameFacade* facade) : facade(facade) {
}

bool MoveHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string unit;
	std::string to;
	std::string coordinates;
	int unitId, x, y;
	char comma;

	stream >> command;

	if (command == "move" &&
		stream >> unit >> unitId >> to >> coordinates &&
		unit == "unit" && to == "to") {

		std::istringstream coordinateStream(coordinates);

		if (!(coordinateStream >> x >> comma >> y) || comma != ',') {
			return false;
		}

		if (facade == nullptr) {
			return false;
		}

		facade->moveUnit(unitId, x, y);
		return true;
	}

	if (next_) {
		return next_->handle(cmd);
	}

	return false;
}

AttackHandler::AttackHandler(GameFacade* facade) : facade(facade) {
}

bool AttackHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string unit;
	std::string target;
	int attackerId, targetId;

	stream >> command;

	if (command == "attack" &&
		stream >> unit >> attackerId >> target >> targetId &&
		unit == "unit" && target == "target") {

		if (facade == nullptr) {
			return false;
		}

		facade->attack(attackerId, targetId);
		return true;
	}

	if (next_) {
		return next_->handle(cmd);
	}

	return false;
}

CollectHandler::CollectHandler(GameFacade* facade) : facade(facade) {
}

bool CollectHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string unit;
	std::string from;
	int unitId, resourcePointId;

	stream >> command;

	if (command == "collect" &&
		stream >> unit >> unitId >> from >> resourcePointId &&
		unit == "unit" && from == "from") {

		if (facade == nullptr) {
			return false;
		}

		facade->collectResource(unitId, resourcePointId);
		return true;
	}

	if (next_) {
		return next_->handle(cmd);
	}

	return false;
}

HealHandler::HealHandler(GameFacade* facade) : facade(facade) {
}

bool HealHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	int unitId, targetId;

	stream >> command;

	if (command == "heal" && stream >> unitId >> targetId) {
		if (facade == nullptr) {
			return false;
		}

		facade->heal(unitId, targetId);
		return true;
	}

	if (next_) {
		return next_->handle(cmd);
	}

	return false;
}

BuildHandler::BuildHandler(GameFacade* facade) : facade(facade) {
}

bool BuildHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string buildingType;
	std::string at;
	std::string coordinates;
	int x, y;
	char comma;

	stream >> command;

	if (command == "build" &&
		stream >> buildingType >> at >> coordinates &&
		at == "at") {

		std::istringstream coordinateStream(coordinates);

		if (!(coordinateStream >> x >> comma >> y) || comma != ',') {
			return false;
		}

		if (facade == nullptr) {
			return false;
		}

		if (buildingType == "barracks") {
			buildingType = "Barracks";
		}
		else if (buildingType == "powerplant") {
			buildingType = "PowerPlant";
		}
		else if (buildingType == "laboratory") {
			buildingType = "Laboratory";
		}
		else if (buildingType == "warehouse") {
			buildingType = "Warehouse";
		}
		else if (buildingType == "hospital") {
			buildingType = "Hospital";
		}

		facade->buildBuilding(buildingType, x, y);
		return true;
	}

	if (next_) {
		return next_->handle(cmd);
	}

	return false;
}

ResearchHandler::ResearchHandler(GameFacade* facade) : facade(facade) {
}

bool ResearchHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string technology;
	int technologyId = 0;

	stream >> command;

	if (command == "research" && stream >> technology) {
		if (facade == nullptr) {
			return false;
		}

		if (technology == "attack_upgrade") {
			technologyId = 1;
		}
		else if (technology == "defense_upgrade") {
			technologyId = 2;
		}
		else if (technology == "production_upgrade") {
			technologyId = 3;
		}
		else {
			return false;
		}

		facade->research(technologyId);
		return true;
	}

	if (next_) {
		return next_->handle(cmd);
	}

	return false;
}

ProduceHandler::ProduceHandler(GameFacade* facade) : facade(facade) {
}

bool ProduceHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string unitType;
	std::string in;
	int buildingId;

	stream >> command;

	if (command == "produce" &&
		stream >> unitType >> in >> buildingId &&
		in == "in") {

		if (facade == nullptr) {
			return false;
		}

		if (unitType == "infantry") {
			unitType = "Infantry";
		}

		facade->produceUnit(buildingId, unitType);
		return true;
	}

	if (next_) {
		return next_->handle(cmd);
	}

	return false;
}

StatsHandler::StatsHandler(GameFacade* facade) : facade(facade) {
}

bool StatsHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string parameter;

	stream >> command >> parameter;

	if (command == "stats") {
		if (facade == nullptr) {
			return false;
		}

		if (parameter.empty() ||
			parameter == "units" ||
			parameter == "buildings" ||
			parameter == "resources") {
			facade->getStats(parameter);
			return true;
		}
	}

	if (next_) {
		return next_->handle(cmd);
	}

	return false;
}

DistributeHandler::DistributeHandler(GameFacade* facade) : facade(facade) {
}

bool DistributeHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string resourceType;
	std::string to;
	std::string buildingType;
	int amount;

	stream >> command;

	if (command == "distribute" &&
		stream >> resourceType >> to >> buildingType >> amount &&
		to == "to") {

		if (facade == nullptr) {
			return false;
		}

		if (buildingType == "barracks") {
			buildingType = "Barracks";
		}

		facade->distributeResources(resourceType, amount, buildingType);
		return true;
	}

	if (next_) {
		return next_->handle(cmd);
	}

	return false;
}