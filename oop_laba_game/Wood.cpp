#include "Wood.h"

Wood::Wood(int amount) : amount(amount > 0 ? amount : 0) {}

int Wood::getAmount() const {
	return amount;
}

void Wood::setAmount(int amount) {
	this->amount = amount > 0 ? amount : 0;
}

void Wood::increase(int amount) {
	if (amount <= 0) return;
	this->amount += amount;
}

void Wood::decrease(int amount) {
	if (amount <= 0) return;
	this->amount -= amount;

	if (this->amount < 0) {
		this->amount = 0;
	}
}