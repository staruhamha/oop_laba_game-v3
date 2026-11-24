#pragma once

#include "Building.h"

class Barracks : public Building {
public:
	Barracks(int id, int x, int y);
	void update() override;
	void produce(const std::string& unitType) override;
};

class PowerPlant : public Building {
public:
	PowerPlant(int id, int x, int y);
	void update() override;
	void produce(const std::string& unitType) override;
};

class Laboratory : public Building {
public:
	Laboratory(int id, int x, int y);
	void update() override;
	void produce(const std::string& unitType) override;
};

class Warehouse : public Building {
public:
	Warehouse(int id, int x, int y);
	void update() override;
	void produce(const std::string& unitType) override;
};

class Hospital : public Building {
public:
	Hospital(int id, int x, int y);
	void update() override;
	void produce(const std::string& unitType) override;
};
