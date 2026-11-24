#include "ResourcePoint.h"

ResourcePoint::ResourcePoint(int id, const std::string& resourceType, int amount)
	: id(id), resourceType(resourceType), amount(amount) {
}

int ResourcePoint::getId() const {
	return id;
}

std::string ResourcePoint::getResourceType() const {
	return resourceType;
}

int ResourcePoint::getAmount() const {
	return amount;
}

int ResourcePoint::collect(int requestedAmount) {
	if (requestedAmount <= 0 || amount <= 0) {
		return 0;
	}

	int collected = requestedAmount;

	if (collected > amount) {
		collected = amount;
	}

	amount -= collected;

	return collected;
}