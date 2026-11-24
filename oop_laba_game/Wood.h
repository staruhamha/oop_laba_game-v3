#pragma once

class Wood {
private:
	int amount;

public:
	Wood(int amount);

	int getAmount() const;
	void setAmount(int amount);

	void increase(int amount);
	void decrease(int amount);
};