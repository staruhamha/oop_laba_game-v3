#include "Metal.h"

Metal::Metal(int amount) : amount(amount > 0 ? amount : 0) {}

int Metal::getAmount() const {
	return amount;
}

void Metal::setAmount(int amount) {
	this->amount = amount > 0 ? amount : 0;
}

void Metal::increase(int amount) {
	if (amount <= 0) return;
	this->amount += amount;
}

void Metal::decrease(int amount) {
	if (amount <= 0) return;
	this->amount -= amount;

	if (this->amount < 0) {
		this->amount = 0;
	}
}