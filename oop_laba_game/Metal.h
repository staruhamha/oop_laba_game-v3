#pragma once

class Metal {
private:
	int amount;

public:
	Metal(int amount);

	int getAmount() const;
	void setAmount(int amount);

	void increase(int amount);
	void decrease(int amount);
};