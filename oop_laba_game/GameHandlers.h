#pragma once

#include "Handler.h"
#include <string>

class GameFacade;

class CreateHandler : public Handler {
private:
	GameFacade* facade;

public:
	CreateHandler(GameFacade* facade);
	bool handle(const std::string& cmd) override;
};

class MoveHandler : public Handler {
private:
	GameFacade* facade;

public:
	MoveHandler(GameFacade* facade);
	bool handle(const std::string& cmd) override;
};

class AttackHandler : public Handler {
private:
	GameFacade* facade;

public:
	AttackHandler(GameFacade* facade);
	bool handle(const std::string& cmd) override;
};

class CollectHandler : public Handler {
private:
	GameFacade* facade;

public:
	CollectHandler(GameFacade* facade);
	bool handle(const std::string& cmd) override;
};

class HealHandler : public Handler {
private:
	GameFacade* facade;

public:
	HealHandler(GameFacade* facade);
	bool handle(const std::string& cmd) override;
};

class BuildHandler : public Handler {
private:
	GameFacade* facade;

public:
	BuildHandler(GameFacade* facade);
	bool handle(const std::string& cmd) override;
};

class ResearchHandler : public Handler {
private:
	GameFacade* facade;

public:
	ResearchHandler(GameFacade* facade);
	bool handle(const std::string& cmd) override;
};

class ProduceHandler : public Handler {
private:
	GameFacade* facade;

public:
	ProduceHandler(GameFacade* facade);
	bool handle(const std::string& cmd) override;
};

class StatsHandler : public Handler {
private:
	GameFacade* facade;

public:
	StatsHandler(GameFacade* facade);
	bool handle(const std::string& cmd) override;
};

class DistributeHandler : public Handler {
private:
	GameFacade* facade;

public:
	DistributeHandler(GameFacade* facade);
	bool handle(const std::string& cmd) override;
};