#include "Unit.h"
#include <algorithm>

namespace {
    int nextUnitId = 1;
}

Unit::Unit(int x, int y, const Health& health, const Armor& armor, const Attack& attack, UnitType type) : id(nextUnitId++), x(x), y(y), mana(0), currentOrder(""), health(health), armor(armor), attackComponent(attack), typeInfo(UnitTypeInfo::getInfo(type)) {
}

Unit::Unit(const Unit& other) : id(nextUnitId++), x(other.x), y(other.y), mana(other.mana), wood(other.wood), metal(other.metal), energy(other.energy), currentOrder(other.currentOrder), health(other.health), armor(other.armor),attackComponent(other.attackComponent), typeInfo(other.typeInfo) {
}

Unit::~Unit() = default;

int Unit::getId() const 
{
    return id; 
}

int Unit::getX() const
{
    return x;
}

int Unit::getY() const
{
    return y;
}

const std::string& Unit::getCurrentOrder() const {
    return currentOrder;
}

void Unit::setCurrentOrder(const std::string& order) {
    currentOrder = order;
}

const Health& Unit::getHealth() const
{
    return health;
}

const Armor& Unit::getArmor() const
{
    return armor;
}

const Attack& Unit::getAttack() const
{
    return attackComponent;
}

int Unit::getMana() const {
    return mana;
}

void Unit::increaseMana(int amount) {
    if (amount > 0) {
        mana += amount;
    }
}

int Unit::getWood() const {
    return wood;
}

int Unit::getMetal() const {
    return metal;
}

int Unit::getEnergy() const {
    return energy;
}

void Unit::addWood(int amount) {
    if (amount > 0) {
        wood += amount;
    }
}

void Unit::addMetal(int amount) {
    if (amount > 0) {
        metal += amount;
    }
}

void Unit::addEnergy(int amount) {
    if (amount > 0) {
        energy += amount;
    }
}

void Unit::move(int dx, int dy)
{
    x += dx;
    y += dy;
}

void Unit::takeDamage(int damage) {
    bool wasAlive = !health.isZero();

    int remainDamage = armor.reduceDamage(damage);
    health.decrease(remainDamage);

    notify(UnitEvent(UnitEventType::Damaged, id, remainDamage));

    if (wasAlive && health.isZero()) {
        notify(UnitEvent(UnitEventType::Destroyed, id, 0));
    }
}

void Unit::takeDamageAfterArmor(int damage) {
    bool wasAlive = !health.isZero();

    health.decrease(damage);

    notify(UnitEvent(UnitEventType::Damaged, id, damage));

    if (wasAlive && health.isZero()) {
        notify(UnitEvent(UnitEventType::Destroyed, id, 0));
    }
}

void Unit::restoreHealth(int amount) {
    health.increase(amount);
}

void Unit::increaseAttack(int amount) {
    attackComponent.setDamage(attackComponent.getDamage() + amount);
}

int Unit::calculateDamage() const {
    return attackComponent.calculateDamage(0);
}

void Unit::attack(Unit& target) const {
    int damage = calculateDamage();
    target.takeDamage(damage);
}

const UnitTypeInfo& Unit::getTypeInfo() const {
    return *typeInfo;
}

void Unit::subscribe(IObserver* observer) {
    if (observer != nullptr &&
        std::find(observers.begin(), observers.end(), observer) == observers.end()) {
        observers.push_back(observer);
    }
}

void Unit::unsubscribe(IObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Unit::notify(const UnitEvent& event) {
    std::vector<IObserver*> observersCopy = observers;

    for (IObserver* observer : observersCopy) {
        observer->onUnitEvent(event);
    }
}