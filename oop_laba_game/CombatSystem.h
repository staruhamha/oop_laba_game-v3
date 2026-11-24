#pragma once

#include "Unit.h"

class CombatSystem {
public:
	int calculateDamage(Unit& attacker, Unit& target);
	void attack(Unit& attacker, Unit& target);
};