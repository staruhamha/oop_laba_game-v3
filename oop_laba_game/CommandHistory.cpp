#include "CommandHistory.h"
#include "Command.h"

void CommandHistory::push(std::shared_ptr<Command> command) {
	if (command) {
		history.push(command);
	}
}

void CommandHistory::undo() {
	if (!history.empty()) {
		history.pop();
	}
}

std::shared_ptr<Command> CommandHistory::getLastCommand() const {
	if (history.empty()) {
		return nullptr;
	}

	return history.top();
}