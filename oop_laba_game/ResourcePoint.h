#pragma once

#include <string>

class ResourcePoint {
private:
	int id;
	std::string resourceType;
	int amount;

public:
	ResourcePoint(int id, const std::string& resourceType, int amount);

	int getId() const;
	std::string getResourceType() const;
	int getAmount() const;

	int collect(int requestedAmount);
};