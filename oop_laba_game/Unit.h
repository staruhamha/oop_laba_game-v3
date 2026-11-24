#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Health.h"
#include "Armor.h"
#include "Attack.h"
#include "UnitTypeInfo.h"
#include "IObservable.h"


class Unit : public IObservable {
private:
	int id;
	int x;
	int y;
	int mana = 0;

	int wood = 0;
	int metal = 0;
	int energy = 0;

	std::string currentOrder;

	Health health;
	Armor armor;
	Attack attackComponent;
	std::shared_ptr<UnitTypeInfo> typeInfo;

	std::vector<IObserver*> observers;

public:
	Unit(int x, int y, const Health& health, const Armor& armor, const Attack& attack, UnitType type);
	Unit(const Unit& other);
	Unit& operator=(const Unit& other) = delete;
	virtual ~Unit();

	int getId() const;
	int getX() const;
	int getY() const;
	const std::string& getCurrentOrder() const;
	void setCurrentOrder(const std::string& order);

	int getMana() const;
	void increaseMana(int amount);

	int getWood() const;
	int getMetal() const;
	int getEnergy() const;

	void addWood(int amount);
	void addMetal(int amount);
	void addEnergy(int amount);

	const Health& getHealth() const;
	const Armor& getArmor() const;
	const Attack& getAttack() const;

	virtual void move(int dx, int dy) = 0;
	virtual std::string getType() const = 0;
	virtual std::unique_ptr<Unit> clone() const = 0;

	virtual void takeDamage(int damage) = 0;
	void takeDamageAfterArmor(int damage);
	void restoreHealth(int amount);
	void increaseAttack(int amount);
	int calculateDamage() const;

	virtual void attack(Unit& target) const = 0;

	const UnitTypeInfo& getTypeInfo() const;

	void subscribe(IObserver* observer) override;
	void unsubscribe(IObserver* observer) override;
	void notify(const UnitEvent& event) override;
};
