#pragma once

#include <thread>
#include <atomic>
#include <future>

#include "AI\AI.hpp"
#include "map\Grid.hpp"
#include "Game\Player\APlayer.h"

class IAPlayer : public APlayer
{
public:
	IAPlayer(PlayerId id, std::string name, IAI<Grid<Cell>>::Function func);
	~IAPlayer();
public:
	bool							isCreated() const;
	bool							isRunning() const;
	void							setMethod(IAI<Grid<Cell>>::Function method);
	void							newAction(const Grid<Cell>& map, const Referee<Grid<Cell>>& referee);
	double							getActionTime() const;
public:
	virtual std::pair<int, int>		getNextAction();
private:
	AIFactory<Grid<Cell>>::AsyncAI	ia;
};

