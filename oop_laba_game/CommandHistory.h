#pragma once

#include <memory>
#include <stack>

class Command;

class CommandHistory {
private:
	std::stack<std::shared_ptr<Command>> history;

public:
	void push(std::shared_ptr<Command> command);
	void undo();
	std::shared_ptr<Command> getLastCommand() const;
};