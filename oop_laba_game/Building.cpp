#include "Building.h"

Building::Building(int id, const std::string& type, int cost, int x, int y)
	: id(id), type(type), cost(cost), health(500), x(x), y(y), buildProgress(0) {
}

int Building::getId() const {
	return id;
}

const std::string& Building::getType() const {
	return type;
}

const std::string& Building::getName() const {
	return type;
}

int Building::getCost() const {
	return cost;
}

int Building::getHealth() const {
	return health;
}

int Building::getX() const {
	return x;
}

int Building::getY() const {
	return y;
}

int Building::getBuildProgress() const {
	return buildProgress;
}

bool Building::isBuilt() const {
	return buildProgress >= 100;
}

void Building::completeConstruction() {
	buildProgress = 100;
}

void Building::addWood(int amount) {
	if (amount > 0) {
		wood += amount;
	}
}

int Building::getWood() const {
	return wood;
}