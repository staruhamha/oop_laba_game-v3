#pragma once

class Energy {
private:
	int amount;

public:
	Energy(int amount);

	int getAmount() const;
	void setAmount(int amount);

	void increase(int amount);
	void decrease(int amount);
};