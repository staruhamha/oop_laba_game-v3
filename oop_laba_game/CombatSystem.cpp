#include "CombatSystem.h"

int CombatSystem::calculateDamage(Unit& attacker, Unit& target) {
	int enemyArmor = target.getArmor().getCurrentArmor();

	return attacker.getAttack().calculateDamage(enemyArmor);
}

void CombatSystem::attack(Unit& attacker, Unit& target) {
	int damage = calculateDamage(attacker, target);
	target.takeDamageAfterArmor(damage);
}