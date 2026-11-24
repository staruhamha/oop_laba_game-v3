#include "Energy.h"

Energy::Energy(int amount) : amount(amount > 0 ? amount : 0) {}

int Energy::getAmount() const {
	return amount;
}

void Energy::setAmount(int amount) {
	this->amount = amount > 0 ? amount : 0;
}

void Energy::increase(int amount) {
	if (amount <= 0) return;
	this->amount += amount;
}

void Energy::decrease(int amount) {
	if (amount <= 0) return;
	this->amount -= amount;

	if (this->amount < 0) {
		this->amount = 0;
	}
}