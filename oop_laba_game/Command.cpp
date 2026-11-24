#include "Command.h"

Command::Command(std::shared_ptr<GameMediator> mediator) : mediator(mediator) {
}

bool Command::isValid() const {
	return mediator != nullptr;
}