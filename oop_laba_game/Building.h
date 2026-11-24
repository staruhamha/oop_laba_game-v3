#pragma once

#include <string>

class Building {
private:
	int id;
	std::string type;
	int cost;
	int health;
	int x;
	int y;
	int buildProgress;
	int wood = 0;

public:
	Building(int id, const std::string& type, int cost, int x = 0, int y = 0);
	virtual ~Building() = default;

	int getId() const;
	const std::string& getType() const;
	const std::string& getName() const;
	int getCost() const;
	int getHealth() const;
	int getX() const;
	int getY() const;
	int getBuildProgress() const;
	bool isBuilt() const;

	void completeConstruction();

	void addWood(int amount);
	int getWood() const;

	virtual void update() = 0;
	virtual void produce(const std::string& unitType) = 0;
};
