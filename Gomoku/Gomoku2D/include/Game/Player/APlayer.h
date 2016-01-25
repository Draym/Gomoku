#pragma once

#include "Utils\Exception.h"
#include "referee\IReferee.hpp"

enum class PlayerType { HUMAN, IA };

class APlayer
{
protected:
	APlayer(PlayerId id, PlayerType type, std::string name);
public:
	virtual ~APlayer();
public:
	virtual void					reset();
	virtual PlayerId				getId() const;
	virtual PlayerType				getType() const;
	virtual std::pair<int, int>		getNextAction();
	virtual std::string				getName() const;
private:
	PlayerId			id;
	PlayerType			type;
	std::string			name;
};