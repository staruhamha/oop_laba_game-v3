#pragma once

#include <memory>
#include <string>

class Base;
class Unit;

class UnitManager {
private:
	Base* base;

public:
	UnitManager(Base* base);

	std::shared_ptr<Unit> createUnit(int x, int y, const std::string& type);
	std::shared_ptr<Unit> getUnit(int unitId);
	std::shared_ptr<Unit> getUnitById(int unitId);
	bool moveUnit(int unitId, int x, int y);
	bool removeUnit(int unitId);
};