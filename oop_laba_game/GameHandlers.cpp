#include "GameHandlers.h"
#include "GameFacade.h"
#include <iostream>
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

	if (command == "create") {
		if (!(stream >> unit >> type >> at >> coordinates) ||
			unit != "unit" || at != "at") {
			std::cout << "Неверные аргументы команды create" << std::endl;
			return true;
		}

		std::istringstream coordinateStream(coordinates);

		if (!(coordinateStream >> x >> comma >> y) || comma != ',') {
			std::cout << "Неверные координаты" << std::endl;
			return true;
		}

		if (facade == nullptr) return true;

		if (type == "infantry") type = "Infantry";
		else if (type == "scout") type = "Scout";

		facade->createUnit(type, x, y);
		return true;
	}

	if (next_) return next_->handle(cmd);
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

	if (command == "move") {
		if (!(stream >> unit >> unitId >> to >> coordinates) ||
			unit != "unit" || to != "to") {
			std::cout << "Неверные аргументы команды move" << std::endl;
			return true;
		}

		std::istringstream coordinateStream(coordinates);

		if (!(coordinateStream >> x >> comma >> y) || comma != ',') {
			std::cout << "Неверные координаты" << std::endl;
			return true;
		}

		if (facade == nullptr) {
			return true;
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

	if (command == "attack") {
		if (!(stream >> unit >> attackerId >> target >> targetId) ||
			unit != "unit" || target != "target") {
			std::cout << "Неверные аргументы команды attack" << std::endl;
			return true;
		}

		if (facade == nullptr) {
			return true;
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

	if (command == "collect") {
		if (!(stream >> unit >> unitId >> from >> resourcePointId) ||
			unit != "unit" || from != "from") {
			std::cout << "Неверные аргументы команды collect" << std::endl;
			return true;
		}

		if (facade == nullptr) {
			return true;
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

	if (command == "heal") {
		if (!(stream >> unitId >> targetId)) {
			std::cout << "Неверные аргументы команды heal" << std::endl;
			return true;
		}

		if (facade == nullptr) return true;

		facade->heal(unitId, targetId);
		return true;
	}

	if (next_) return next_->handle(cmd);
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

	if (command == "build") {
		if (!(stream >> buildingType >> at >> coordinates) || at != "at") {
			std::cout << "Неверные аргументы команды build" << std::endl;
			return true;
		}

		std::istringstream coordinateStream(coordinates);

		if (!(coordinateStream >> x >> comma >> y) || comma != ',') {
			std::cout << "Неверные координаты" << std::endl;
			return true;
		}

		if (facade == nullptr) return true;

		if (buildingType == "barracks") buildingType = "Barracks";
		else if (buildingType == "powerplant") buildingType = "PowerPlant";
		else if (buildingType == "laboratory") buildingType = "Laboratory";
		else if (buildingType == "warehouse") buildingType = "Warehouse";
		else if (buildingType == "hospital") buildingType = "Hospital";
		else {
			std::cout << "Неизвестный тип здания" << std::endl;
			return true;
		}

		facade->buildBuilding(buildingType, x, y);
		return true;
	}

	if (next_) return next_->handle(cmd);
	return false;
}

ResearchHandler::ResearchHandler(GameFacade* facade) : facade(facade) {
}

bool ResearchHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string technology;

	stream >> command;

	if (command == "research") {
		if (!(stream >> technology)) {
			std::cout << "Неверные аргументы команды research" << std::endl;
			return true;
		}

		if (technology != "attack_upgrade" &&
			technology != "defense_upgrade" &&
			technology != "production_upgrade") {
			std::cout << "Неизвестная технология" << std::endl;
			return true;
		}

		if (facade == nullptr) return true;

		facade->research(technology);
		return true;
	}

	if (next_) return next_->handle(cmd);
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

	if (command == "produce") {
		if (!(stream >> unitType >> in >> buildingId) || in != "in") {
			std::cout << "Неверные аргументы команды produce" << std::endl;
			return true;
		}

		if (facade == nullptr) return true;

		if (unitType == "infantry") unitType = "Infantry";

		facade->produceUnit(buildingId, unitType);
		return true;
	}

	if (next_) return next_->handle(cmd);
	return false;
}

StatsHandler::StatsHandler(GameFacade* facade) : facade(facade) {
}

bool StatsHandler::handle(const std::string& cmd) {
	std::istringstream stream(cmd);
	std::string command;
	std::string parameter;

	stream >> command;

	if (command == "stats") {
		stream >> parameter;

		if (!parameter.empty() &&
			parameter != "units" &&
			parameter != "buildings" &&
			parameter != "resources" &&
			parameter != "log") {
			std::cout << "Неверный параметр команды stats" << std::endl;
			return true;
		}

		if (facade == nullptr) return true;

		if (parameter == "log") {
			facade->showCommandLog();
		}
		else {
			facade->getStats(parameter);
		}

		return true;
	}

	if (next_) return next_->handle(cmd);
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

	if (command == "distribute") {
		if (!(stream >> resourceType >> to >> buildingType >> amount) ||
			to != "to" || amount <= 0) {
			std::cout << "Неверные аргументы команды distribute" << std::endl;
			return true;
		}

		if (facade == nullptr) return true;

		if (buildingType == "barracks") buildingType = "Barracks";

		facade->distributeResources(resourceType, amount, buildingType);
		return true;
	}

	if (next_) return next_->handle(cmd);
	return false;
}