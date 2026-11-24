#pragma once

#include <memory>

class GameMediator;

class Command {
protected:
	std::shared_ptr<GameMediator> mediator;

	bool isValid() const;

public:
	Command(std::shared_ptr<GameMediator> mediator);
	virtual ~Command() = default;

	virtual void execute() = 0;
};