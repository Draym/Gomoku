#pragma once

#include "APlayer.h"

class HumanPlayer : public APlayer
{
public:
	HumanPlayer(PlayerId id, std::string name);
	~HumanPlayer();
};

